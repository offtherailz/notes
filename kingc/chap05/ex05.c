#include <stdio.h>

int main(void)
{
    float taxable_income;

    printf("Enter your taxable income: ");
    scanf("%f", &taxable_income);

    printf("Tax due: ");
    if (taxable_income < 750.00f)
        printf("%.2f", taxable_income * .01f);
    else if (taxable_income < 2250.00f)
        printf("%.2f", (taxable_income - 750.00f) * .02f + 7.50f);
    else if (taxable_income < 3750.00f)
        printf("%.2f", (taxable_income - 2250.00f) * .03f + 37.50f);
    else if (taxable_income < 5250.00f)
        printf("%.2f", (taxable_income - 3750.00f) * .04f + 82.50f);
    else if (taxable_income < 7000.00f)
        printf("%.2f", (taxable_income - 5250.00f) * .05 + 142.50f);
    else
        printf("%.2f", (taxable_income - 7000.00f) * .06 + 230.00f);
    printf("\n");

    return 0;
}
