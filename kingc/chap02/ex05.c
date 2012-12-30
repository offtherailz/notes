#include <stdio.h>

int main(void)
{
    int x;
    int a, b, c, d, e, f;

    printf("Enter an number for x: ");
    scanf("%d", &x);

    a = 3 * (x * x * x * x * x);
    b = 2 * (x * x * x * x);
    c = 5 * (x * x * x);
    d = x * x;
    e = (7 * x);
    f = 6;

    printf("Polynomial for %d: %d\n", x,
            ((((a + b) - c) - d) + e) - f);

    return 0;
}
