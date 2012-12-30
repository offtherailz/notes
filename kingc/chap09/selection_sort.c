#include <stdio.h>
#include <stdlib.h>

#define N 10

void selection_sort(int n, int a[n]);
int max_idx(int n, int a[n]);
void move_last(int largest_idx, int last_idx,  int a[]);

int
main(void)
{
	int i, nums[N];

	printf("Enter %d integers: ", N);
	for (i = 0; i < N; i++)
		scanf("%d", &nums[i]);

	selection_sort(N, nums);

	printf("Sorted: ");
	for (i = 0; i < N; i++)
		printf("%d ", nums[i]);
	printf("\n");

	exit(EXIT_SUCCESS);
}

void
selection_sort(int n, int a[n])
{
	if (n < 2)
		return;

	move_last(max_idx(n, a), n - 1, a);
	selection_sort(n - 1, a);
}

void
move_last(int largest_idx, int last_idx, int a[])
{
	int tmp;

	tmp = a[last_idx];
	a[last_idx] = a[largest_idx];
	a[largest_idx] = tmp;
}

int
max_idx(int n, int a[n])
{
	int i, idx, max;
	idx = 0;
	max = a[idx];

	for (i = 1; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
			idx = i;
		}
	}

	return idx;
}
