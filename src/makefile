#ifj 2021 - makefile
#autors:xkomar33,xmatus35,xkriva30,xtverd01
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