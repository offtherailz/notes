#include <stdio.h>

int main(void)
{
    int speed;

    printf("What is the wind's speed in knots? ");
    scanf("%d", &speed);

    printf("On the Beaufort scale, the wind is ");

    if (speed < 1) printf("calm.\n");
    else if (speed <= 3) printf("light air.\n");
    else if (speed <= 27) printf("breeze.\n");
    else if (speed <= 47) printf("gale.\n");
    else if (speed <= 63) printf("storm.\n");
    else printf("hurricane.\n");


    return 0;
}
