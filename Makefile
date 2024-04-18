CC=gcc
CCOPTS=-Wall -Wextra -pthread
LIBS=eventbuf.c

SRCS=$(wildcard *.c)
TARGETS=$(SRCS:.c=)

.PHONY: all clean eventbuf

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

eventbuf.c:

%: %.c
	$(CC) $(CCOPTS) -o $@ $< $(LIBS)