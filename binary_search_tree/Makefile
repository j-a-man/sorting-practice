CC = gcc
CFLAGS = -g -Wall -std=c2x

all: bst
	$(CC) $(CFLAGS) -o bst bst.c

bst: bst.c
	$(CC) $(CFLAGS) -o bst bst.c

clean:
	rm -f bst