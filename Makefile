CC=gcc
CVER=-std=c99
CFLAGS=-Wall -Wpedantic -O3

regnr: regnr.o
	$(CC) -o regnr regnr.o $(CFLAGS)

%.o: %.c
	$(CC) $(CVER) -c -o $@ $< $(CFLAGS)

