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
    `sem_open_temp`: 
    `eventbuf_create`: malloc eventbuf and initialize head and tail as NULL
    `eventbuf_free`: free eventbuf
    `eventbuf_add`: add a new node to the eventbuf
    `eventbuf_get`: remove a node from the eventbuf
    `eventbuf_empty`: returns true if the eventbuf is empty

## Notes