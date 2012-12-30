#include <stdio.h>

int main(void)
{
    float radius = 10.0f;

    printf("The volume of a sphere with a radius of %.2f is %.2f.\n",
            radius, 4.0f / 3.0f * 3.14f * radius * radius * radius);

    return 0;
}
