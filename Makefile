CC=gcc
CFLAGS = -c -std=c99 -Wall

all: Dictionary

Dictionary: Source.o set.o dictionary.o
	$(CC) Source.o set.o dictionary.o -o Dictionary

Source.o: Source.c
	$(CC) $(CFLAGS) Source.c

set.o: set.c
	$(CC) $(CFLAGS) set.c
	
dictionary.o: dictionary.c
	$(CC) $(CFLAGS) dictionary.c

clean:
	rm -f *o

#%: %.c; = tab space
#gcc Source.c set.c dictionary.c - o Dictionary

