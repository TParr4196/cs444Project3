#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include "eventbuf.h"

struct eventbuf *eb;
int event_production;//how many items each producer should make

sem_t *items; //how many items are in the queue
sem_t *mutex; //acts as a mutex
sem_t *spaces;//how much space is available in queue storage

int producers;//helps keep track of when to turn off consumers

void *producer(void *arg){
    int *id=arg;
    int produced = 0;
    while(produced<event_production){
        //this semaphore ordering waits for a space in queue, grabs the mutex, and then adds an item to the queue when done.
        sem_wait(spaces);
        sem_wait(mutex);
        printf("P%d: adding event %d\n", *id,*id*100+produced);
        eventbuf_add(eb, *id*100+produced);
        produced++;
        sem_post(mutex);
        sem_post(items);
    }
    printf("P%d: exiting\n", *id);
    producers--;
    return NULL;
}

void *consumer(void *arg){
    int *id=arg;

    //checks if events are still being created
    while(producers>0 || eventbuf_empty(eb)!=1){
        //this semaphore ordering waits for an item to enter the queue, grabs the mutex, and then adds a space to the storage when done.
        sem_wait(items);
        sem_wait(mutex);
        
        //needed to keep items semaphore from locking threads out on the last item
        if(producers==0){
            sem_post(items);
            if(eventbuf_empty(eb)!=1){
                printf("C%d: got event %d\n", *id, eventbuf_get(eb));
            }
        }else{
            printf("C%d: got event %d\n", *id, eventbuf_get(eb));
        }

        sem_post(mutex);
        sem_post(spaces);
    }
    printf("C%d: exiting\n", *id);
    return NULL;
}

sem_t *sem_open_temp(const char *name, int value)
{
    sem_t *sem;

    // Create the semaphore
    if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
        return SEM_FAILED;

    // Unlink it so it will go away after this process exits
    if (sem_unlink(name) == -1) {
        sem_close(sem);
        return SEM_FAILED;
    }

    return sem;
}

//comment structure borrowed from Brian Hall's "reservations.c"
int main(int argc, char *argv[]){
    //Verify or provide intended usage
    if (argc != 5) {
        fprintf(stderr, "usage: pc producers consumers event_production event_storage\n");
        exit(1);
    }

    //Initialize runtime variables
    producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    event_production = atoi(argv[3]);
    items=sem_open_temp("Project_3_items", 0);
    mutex=sem_open_temp("Project_3_mutex", 1);
    spaces=sem_open_temp("Project_3_spaces", atoi(argv[4]));
    if(items==SEM_FAILED||mutex==SEM_FAILED||spaces==SEM_FAILED){
        fprintf(stderr, "semaphore failed to create");
    }

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

    // Wait for all producers to complete
    for (int i = 0; i < producers; i++)
        pthread_join(thread[i], NULL);
    
    // Wait for all consumers to complete
    for (int i = consumers; i < producers+consumers; i++)
        pthread_join(thread[i], NULL);

    //free event buffer
    eventbuf_free(eb);
}