#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "eventbuf.h"

struct eventbuf *eb;

void *producer(void *arg){
    int *id=arg;
    printf("%d\n",*id);

    return NULL;
}

void *consumer(void *arg){
    int *id=arg;
    printf("%d\n",*id);

    return NULL;
}

//comment structure borrowed from Brian Hall's "reservations.c"
int main(int argc, char *argv[]){
    //Verify or provide intended usage
    if (argc != 5) {
        fprintf(stderr, "usage: pc producers consumers event_production event_storage\n");
        exit(1);
    }

    //Initialize runtime variables
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    //int event_production = atoi(argv[3]);
    //int event_storage = atoi(argv[4]);

    //allocate event buffer
    eb=eventbuf_create();

    // Allocate thread handle array for all producers and consumers
    pthread_t *thread = calloc(producers+consumers, sizeof *thread);

    // Allocate thread ID array for all producers and consumers
    int *thread_id = calloc(producers+consumers, sizeof *thread_id);

    //Launch producers
    for (int i = 0; i < producers; i++) {
        thread_id[i] = i;
        pthread_create(thread + i, NULL, producer, thread_id + i);
    }

    //Launch consumers
    for (int i = 0; i < consumers; i++) {
        thread_id[i+producers] = i;
        pthread_create(thread + i, NULL, consumer, thread_id + i + producers);
    }

    // Wait for all threads to complete
    for (int i = 0; i < producers+consumers; i++)
        pthread_join(thread[i], NULL);

    //free event buffer
    eventbuf_free(eb);
}