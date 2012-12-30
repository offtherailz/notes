#include <stdio.h>

int main(void)
{
    int x;
    int a, b, c, d, e;

    printf("Enter an number for x: ");
    scanf("%d", &x);

    a = (3 * x) + 2;
    b = (a * x) - 5;
    c = (b * x) - 1;
    d = (c * x) + 7;
    e = (d * x) - 6;

    printf("Polynomial for %d: %d\n", x, e);

    return 0;
}
