CC=gcc
CFLAGS= -g -std=gnu11 -Wall -Wextra -Wpedantic -Wshadow -O3 -lm -lpthread

all: clean build

clean:
	clear && rm -f ../bin/*

build:
	$(CC) -o ../bin/main main.c $(CFLAGS)

run: ../bin/main
	clear && ../bin/main

install: ../bin/main
	sudo cp -f ../bin/main /usr/local/bin/gradient

