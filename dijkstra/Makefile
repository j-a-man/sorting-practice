CC = gcc
CFLAGS = -g -Wall -Wextra -std=c2x

OBJS = \
  dijkstra.o

SRCS = dijkstra.c
HEADERS = dijkstra.h

all: dijkstra

dijkstra: $(OBJS)
	$(CC) $(CFLAGS) -o dijkstra $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f dijkstra *.o