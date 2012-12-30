#include <stdio.h>

#define DIGITS 10

int main(void)
{
    int digit_seen[DIGITS] = {0};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        digit_seen[digit]++;
        n /= 10;
    }

    printf("%-15s", "Digit:");
    for (digit = 0; digit < DIGITS; digit++) {
        printf("%-4d", digit);
    }
    printf("\n");

    printf("%-15s", "Occurrences:");
    for (digit = 0; digit < DIGITS; digit++) {
        printf("%-4d", digit_seen[digit]);
    }
    printf("\n");

    return 0;
}
