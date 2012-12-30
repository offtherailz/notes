#include <stdio.h>

int main(void)
{
    float commission, price, value, rival;
    int share_count;

    printf("Enter the price per share of the stock: ");
    scanf("%f", &price);
    printf("Enter the number of shares: ");
    scanf("%d", &share_count);

    value = price * share_count;

    if (value < 2500.00f)
        commission = 30.00f + .017 * value;
    else if (value < 6250.00f)
        commission = 56.00f + .0066f * value;
    else if (value < 20000.00f)
        commission = 76.00f + .0034f * value;
    else if (value < 50000.00f)
        commission = 100.00f + .0022f * value;
    else if (value < 500000.00f)
        commission = 155.00f + .0011f * value;
    else
        commission = 255.00f + .0009 * value;

    if (commission < 39.00f)
        commission = 39.00f;

    if (value < 2000.00f)
        rival = 33.00f + .03f * share_count;
    else
        rival = 33.00f + .02f * share_count;

    printf("Commission: $%.2f\n", commission);
    printf("Rival's commission: $%.2f\n", rival);

    return 0;
}
