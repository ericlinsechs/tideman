SHELL = /bin/bash

EXEC = tideman 
.PHONY: all
all: $(EXEC)

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

OBJS := cs50.o tideman.o

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@rm $(OBJS)

check: $(EXEC) 
	@~/.local/bin/check50 cs50/problems/2023/x/$(EXEC) 

clean:
	@rm $(EXEC) $(OBJS)
