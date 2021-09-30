CFLAGS=-std=c99 -Wall -pedantic -g
BIN=ifj21
CC=gcc
SRC=$(wildcard *.c)

.PHONY: all build clean

all: build

build: 
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) 
clean:
	rm $(BIN) 