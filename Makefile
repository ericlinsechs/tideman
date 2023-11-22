SHELL = /bin/bash

EXEC = tideman 
.PHONY: all
all: $(EXEC)

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

OBJS := cs50.o tideman.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	rm $(OBJS)

clean:
	rm $(EXEC) $(OBJS)
