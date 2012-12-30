#include <stdio.h>

int main(void)
{
    float input, max;
    max = 0.0f;

    for (;;) {
        printf("Enter a number: ");
        scanf("%f", &input);

        max = (input > max) ? input : max;

        if (input <= 0) break;
    }

    printf("The largest number entered was %.2f.\n", max);

    return 0;
}
