CC=gcc
CVER=-std=c99
CFLAGS=-Wall -Wpedantic -O3

all: regnr poc.out

regnr: regnr.o
	$(CC) -o regnr regnr.o $(CFLAGS)

poc.out: poc.o
	$(CC) -o poc.out poc.o $(CFLAGS)

%.o: %.c
	$(CC) $(CVER) -c -o $@ $< $(CFLAGS)

