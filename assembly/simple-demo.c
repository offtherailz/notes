#include <stdio.h>
#include <stdlib.h>

int
add(int x, int y)
{
	int z;

	z = x + y;

	return z;
}

int main(int argc, const char *argv[])
{
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c;

	char buffer[100];
	gets(buffer);
	puts(buffer);
	c = add(a,b);
	printf("Sum of %d + %d = %d.\n", a, b, c);

	return 0;
}
