#include <stdio.h>

#define ROWS 4
#define COLS 8

int
main(void)
{
	int a[ROWS][COLS], *p, i, j;

	/* Initialize all members of a to 5. */
	for (p = &a[0][0]; p <= &a[ROWS-1][COLS-1]; p++) {
		*p = 5;
	}
	/* Print out what we have so far. */
	for (p = &a[0][0], j = 1; p <= &a[ROWS-1][COLS-1]; p++, j++) {
		printf("%5d", *p);
		if (j % COLS == 0) {
			printf("\n");
		}
	}

	printf("\n");

	/* The book I'm reading - C Programming: A Modern Approach, 2nd ed
	 * by K.N. King - suggests the following as a way of processing one
	 * column of a multidimensional array.
	 *
	 * int (*z)[COLS];
	 * for (z = &a[0]; z < &a[ROWS]; z++)
	 * 	(*z)[3] = 0;
	 *
	 * I find this VERY painful to read or think about. Is there
	 * something wrong with the following that I'm not seeing?
	 */


	/* Iterate over one column, changing its value to 0. */
	for (p = &a[0][3]; p <= &a[ROWS-1][COLS-1]; p += COLS) {
		*p = 0;
	}

	/* Print out new version. */
	for (p = &a[0][0], j = 1; p <= &a[ROWS-1][COLS-1]; p++, j++) {
		printf("%5d", *p);
		if (j % COLS == 0) {
			printf("\n");
		}
	}

	return 0;
}
