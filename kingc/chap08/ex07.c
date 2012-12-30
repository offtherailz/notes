#include <stdio.h>

#define SQUARE 5

int main(void)
{
    int nums[SQUARE][SQUARE];
    int i, j, sum;

    for (i = 0; i < SQUARE; i++) {
        printf("Enter row %d: ", i + 1);
        for (j = 0; j < SQUARE; j++) {
            scanf("%d", &nums[i][j]);
        }
    }

    /* Print row totals. */
    printf("Row totals: ");
    for (i = 0; i < SQUARE; i++) {
        for (j = 0, sum = 0; j < SQUARE; j++) {
            sum += nums[i][j];
        }
        printf("%3d", sum);
    }
    printf("\n");

    /* Print column totals. */
    printf("Column totals: ");
    for (i = 0; i < SQUARE; i++) {
        for (j = 0, sum = 0; j < SQUARE; j++) {
            sum += nums[j][i];
        }
        printf("%3d", sum);
    }
    printf("\n");

    return 0;
}
