#include <stdlib.h>
#include <pthread.h>
#include "eventbuf.h"

struct eventbuf *eb;

int main(int argc, char *argv[]){
    // Parse command line
    if (argc != 4) {
        fprintf(stderr, "usage: pc producers consumers event_production event_storage\n");
        exit(1);
    }

    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    int event_production = atoi(argv[3]);
    int event_storage = atoi(argv[4]);

    //allocate event buffer
    eb=eventbuf_create();

    eventbuf_free(eb);
}