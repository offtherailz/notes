#include <stdio.h>

int main(void)
{
    int hour, minutes;

    printf("Enter a time in 24-hour format: ");
    scanf("%d:%d", &hour, &minutes);

    hour = (hour > 12) ? hour - 12 : hour;
    hour = (hour == 0) ? 12 : hour;

    printf("Equivalent 12-hour time: %d:%02d\n", hour, minutes);

    return 0;
}
