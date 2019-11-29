CC=gcc
CFLAGS= -g -std=c11 -Wall -Wextra -Wpedantic -Wshadow -O3

all: clean build

clean:
	clear && rm -f ../bin/* ./*.o

build:
	$(CC) -o ../bin/main main.c $(CFLAGS)

run: ../bin/main
	clear && ../bin/main

install: main
	sudo ln -sf /home/beronthecolossus/Peki/C/Projects/gradient/bin/main /usr/local/bin/gradient

