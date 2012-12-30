#include <stdio.h>

#define P_I(n) printf(#n " = %d\n", (n))

int main(void)
{
	P_I(4);
	P_I(4 + 2 + 24);
	P_I(2-3-4);

	return 0;
}
