#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "eventbuf.h"

struct eventbuf *eb;

void *producer(void *arg){
    int *id=arg;
}

void *consumer(void *arg){
    int *id=arg;
}

int main(int argc, char *argv[]){
    //Verify or provide intended usage
    if (argc != 4) {
        fprintf(stderr, "usage: pc producers consumers event_production event_storage\n");
        exit(1);
    }

    //Initialize runtime variables
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    int event_production = atoi(argv[3]);
    int event_storage = atoi(argv[4]);

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

    //free event buffer
    eventbuf_free(eb);
}