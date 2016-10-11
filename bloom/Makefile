CC = gcc
CCFLAGS = -O3 -Wall -Wextra -c -g --std=gnu11
LDFLAGS =
LIBS =

.PHONY: all

all: bloom

bloom: main.o bloom.o
	$(CC) $(LDFLAGS) $(LIBS) main.o bloom.o -o $@

.main.o: bloom.h bloom.cpp main.c
	$(CC) $(CCFLAGS) main.c -o main.o

.bloom.o: bloom.h bloom.c
	$(CC) $(CCFLAGS) bloom.c -o bloom.o

clean:
	rm bloom *.o
