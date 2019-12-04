ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o shellfuncs.o shellfuncs.o
	$(CC) -o program main.o shellfuncs.o

main.o: main.c shellfuncs.h
	$(CC) -c main.c

shellfuncs.o: shellfuncs.c shellfuncs.h
	$(CC) -c shellfuncs.c

run:
	./program

clean:
	rm *.o
	rm *~
