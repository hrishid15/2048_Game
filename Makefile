CC=gcc
CFLAGS=-g -std=c99 -Wall #-Werror

all: mp8 run

mp8: main.o game.o getch_fun.o
	$(CC) $(CFLAGS) main.o game.o getch_fun.o -o mp8

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

getch_fun.o: getch_fun.c
	$(CC) $(CFLAGS) -c getch_fun.c

clean:
	rm -f getch_fun.o game.o main.o mp8

run:
	./mp8

.PHONY: all clean run
