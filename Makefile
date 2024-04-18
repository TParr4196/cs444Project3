CC=gcc
CCOPTS=-Wall -Wextra -pthread eventbuf.c
LIBS=

SRCS=$(wildcard *.c)
TARGETS=$(SRCS:.c=)

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%: %.c
	$(CC) $(CCOPTS) -o pc pc.c $(LIBS)
    
