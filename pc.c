#include <pthread.h>

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
}