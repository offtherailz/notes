#include <stdio.h>

int main(void)
{
    int first, second, third;

    printf("Give me a three digit number, and I'll reverse it: ");
    scanf("%1d%1d%1d", &first, &second, &third);

    printf("%d%d%d\n", third, second, first);

    return 0;
}
