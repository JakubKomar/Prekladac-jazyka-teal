CFLAGS=-std=c99 -Wall -pedantic -g

BIN=ifj21
ZIP=xkomar33.zip
CC=gcc
RM=rm -f
SRC=$(wildcard src/**/*.c) $(wildcard src/*.c)
.PHONY: all build d run pack clean test testNoOut

all: build

build: 
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) 
d:
	$(CC) -DDEBUG $(CFLAGS) -o $(BIN) $(SRC) 

pack: clean
	cd src && \
	zip -r $(ZIP) * README.txt && \
	mv $(ZIP) ../

run:
	test -f ifj21 && ./ifj21
valgrind:
	test -f ifj21 && valgrind ./ifj21

clean:
	rm -rf $(BIN) build/ $(ZIP)
test:
	cp ifj21 ./testunity/ifj21 &&\
	cd testunity && \
	python3 tester.py 
testNoOut :
	cp ifj21 ./testunity/ifj21 &&\
	cd testunity && \
	python3 tester.py -o
