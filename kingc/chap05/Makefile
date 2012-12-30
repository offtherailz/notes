CC=gcc-4.2
CFLAGS=-O -Wall -W -pedantic -ansi -std=c99

all : ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex08

ex01 : ex01.o
	$(CC) $(CFLAGS) ex01.o -o ex01.bin

ex01.o : ex01.c
	$(CC) $(CFLAGS) -c ex01.c

ex02 : ex02.o
	$(CC) $(CFLAGS) ex02.o -o ex02.bin

ex02.o : ex02.c
	$(CC) $(CFLAGS) -c ex02.c

ex03 : ex03.o
	$(CC) $(CFLAGS) ex03.o -o ex03.bin

ex03.o : ex03.c
	$(CC) $(CFLAGS) -c ex03.c

ex04 : ex04.o
	$(CC) $(CFLAGS) ex04.o -o ex04.bin

ex04.o : ex04.c
	$(CC) $(CFLAGS) -c ex04.c

ex05 : ex05.o
	$(CC) $(CFLAGS) ex05.o -o ex05.bin

ex05.o : ex05.c
	$(CC) $(CFLAGS) -c ex05.c

ex06 : ex06.o
	$(CC) $(CFLAGS) ex06.o -o ex06.bin

ex06.o : ex06.c
	$(CC) $(CFLAGS) -c ex06.c

ex07 : ex07.o
	$(CC) $(CFLAGS) ex07.o -o ex07.bin

ex07.o : ex07.c
	$(CC) $(CFLAGS) -c ex07.c

ex08 : ex08.o
	$(CC) $(CFLAGS) ex08.o -o ex08.bin

ex08.o : ex08.c
	$(CC) $(CFLAGS) -c ex08.c

clean :
	rm -f *.bin *.o
