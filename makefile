CFLAGS=-std=c99 -Wall -pedantic -g

BIN=ifj21
ZIP=project.zip
CC=gcc
RM=rm -f
SRC=$(wildcard src/**/*.c) $(wildcard src/*.c)
PATHS=$(addprefix ../, $(SRC))
.PHONY: all build doxygen run pack clean

all: build

build: 
	if [ -d "build" ]; then rm -r build; fi && \
	mkdir build && \
	cd build && \
	$(CC) $(CFLAGS) -o $(BIN) $(PATHS) && \
	cp $(BIN) ../

pack: clean
	zip -r $(ZIP) src/ makefile README.txt 

run:
	test -f ifj21 && ./ifj21

doxygen:
	if [ -d "doc" ]; then rm -r doc; fi && \
	mkdir doxygen && \
	doxygen Doxyfile

clean:
	rm -rf $(BIN) build/ $(ZIP)
test:
	cd testunity && \
	python3 tester.py 