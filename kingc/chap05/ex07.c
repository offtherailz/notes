#include <stdio.h>

int main(void)
{
    int first, second, third, fourth;
    int max1, min1, max2, min2;

    printf("Enter four integers: ");
    scanf("%d%d%d%d", &first, &second, &third, &fourth);

    if (first < second) {
        min1 = first;
        max1 = second;
    }
    else {
        min1 = second;
        max1 = first;
    }

    if (third < fourth) {
        min2 = third;
        max2 = fourth;
    }
    else {
        min2 = fourth;
        max2 = third;
    }

    if (min1 < min2)
        printf("Smallest is %d\n", min1);
    else
        printf("Smallest is %d\n", min2);

    if (max1 > max2)
        printf("Largest is %d\n", max1);
    else
        printf("Largest is %d\n", max2);


    return 0;
}
