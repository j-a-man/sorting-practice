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

quick: $(OBJS)
	$(CC) $(CFLAGS) -o quick $(OBJS)

huffman: $(OBJS)
	$(CC) $(CFLAGS) -o huffman $(OBJS)

bin_search: $(OBJS)
	$(CC) $(CFLAGS) -o bin_search $(OBJS)

heap: $(OBJS)
	$(CC) $(CFLAGS) -o heap $(OBJS)

merge: $(OBJS)
	$(CC) $(CFLAGS) -o merge $(OBJS)

bubble: $(OBJS)
	$(CC) $(CFLAGS) -o bubble $(OBJS)

selection: selection.c
	$(CC) $(CFLAGS) selection.c -o selection

insertion: $(OBJS)
	$(CC) $(CFLAGS) -o insertion $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f heap merge bubble selection insertion quick huffman bin_search *.o