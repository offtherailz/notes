#include <stdio.h>

#define NELEMS(a) ((int) (sizeof(a) / sizeof(a[0])))

int main(void)
{
	int nums[25];
	char letters[26];
	nums[0] = 1;
	letters[0] = 'A';

	printf("Number of elements in nums[]: %d\n", NELEMS(nums));
	printf("Number of elements in letters[]: %d.\n", NELEMS(letters));

	return 0;
}
