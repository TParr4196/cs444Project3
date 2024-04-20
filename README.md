# Reservations

## Building
`make` to build. An executable called `pc` will be produced.
`rm -f pc` to clean up executable

## Files
`pc.c`: Project 3 of cs444 designed to explore use of semaphores through producer/consumer threads.
`eventbuf.c`: FIFO queue to help manage events
`eventbuf.h`: Header file and man for `eventbuf.c`

## Data


## Functions
`main`
    `sem_open_temp`: creates a semaphore or returns SEM_FAILED 
        `sem_open`: opens semaphore
        `sem_uplink`: marks the semaphore to close when program exits
    `eventbuf_create`: malloc eventbuf and initialize head and tail as NULL
    `producer`: adds the desired amount of events to the buffer while waiting for space to do so
        `sem_wait`: waits until a semaphore has space for thread to operate
        `eventbuf_add`: add a new node to the eventbuf
        `sem_post`: creates more space for other threads to operate
    `consumer`: removes events from the buffer once they appear until producers are done producing
        `sem_wait`
        `eventbuf_get`: remove a node from the eventbuf
        `eventbuf_empty`: returns true if the eventbuf is empty
        `sem_post`
    `eventbuf_free`: free eventbuf

## Notes
