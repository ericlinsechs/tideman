SHELL = /bin/bash

EXEC = tideman 
.PHONY: all
all: $(EXEC)

CC = gcc
CFLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow 
LDFLAGS = -lm -fsanitize=undefined

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
