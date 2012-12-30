CC=gcc-4.2
CFLAGS=-O -Wall -W -pedantic -ansi -std=c99

all : ex01 ex02 ex08

ex01 : ex01.o
	$(CC) $(CFLAGS) ex01.o -o ex01.bin

ex01.o : ex01.c
	$(CC) $(CFLAGS) -c ex01.c

ex02 : ex02.o
	$(CC) $(CFLAGS) ex02.o -o ex02.bin

ex02.o : ex02.c
	$(CC) $(CFLAGS) -c ex02.c

ex08 : ex08.o
	$(CC) $(CFLAGS) ex08.o -o ex08.bin

ex08.o : ex08.c
	$(CC) $(CFLAGS) -c ex08.c

clean :
	rm -f *.bin *.o
