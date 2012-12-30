CC=gcc-4.2
CFLAGS=-O -Wall -W -pedantic -ansi -std=c99

all : ex01 ex01a

ex01 : ex01.o
	$(CC) $(CFLAGS) ex01.o -o ex01.bin

ex01.o : ex01.c
	$(CC) $(CFLAGS) -c ex01.c

ex01a : ex01a.o
	$(CC) $(CFLAGS) ex01a.o -o ex01a.bin

ex01a.o : ex01a.c
	$(CC) $(CFLAGS) -c ex01a.c

clean :
	rm -f *.bin *.o
