CC = gcc
CFLAGS = -g -Wall -Wextra -std=c2x

OBJS = \
  quick.o \
  huffman.o \
  bin_search.o \
  heap.o \
  merge.o \
  bubble.o \
  selection.o \
  insertion.o

SRCS = quick.c huffman.c bin_search.c heap.c merge.c bubble.c selection.c insertion.c
HEADERS = quick.h huffman.h bin_search.h heap.h merge.h bubble.h selection.h insertion.h

all: quick huffman bin_search heap merge bubble selection insertion

quick: main.o $(OBJS)
	$(CC) $(CFLAGS) -o quick main.o $(OBJS)

huffman: main.o $(OBJS)
	$(CC) $(CFLAGS) -o huffman main.o $(OBJS)

bin_search: main.o $(OBJS)
	$(CC) $(CFLAGS) -o bin_search main.o $(OBJS)

heap: main.o $(OBJS)
	$(CC) $(CFLAGS) -o heap main.o $(OBJS)

merge: main.o $(OBJS)
	$(CC) $(CFLAGS) -o merge main.o $(OBJS)

bubble: main.o $(OBJS)
	$(CC) $(CFLAGS) -o bubble main.o $(OBJS)

selection: main.o $(OBJS)
	$(CC) $(CFLAGS) -o selection main.o $(OBJS)

insertion: main.o $(OBJS)
	$(CC) $(CFLAGS) -o insertion main.o $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f heap merge bubble selection insertion quick huffman bin_search *.o