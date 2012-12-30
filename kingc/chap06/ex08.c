#include <stdio.h>

int main(void)
{
    int idx, days, start;

    printf("Enter number of days in the month: ");
    scanf("%d", &days);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &start);

    for (idx = 1; idx < start; idx++) {
        printf("   ");
    }

    for (idx = 1; idx <= days; idx++) {
        printf("%3d", idx);

        if ((start + idx - 1) % 7 == 0)
            printf("\n");

    }

    printf("\n");

    return 0;
}
