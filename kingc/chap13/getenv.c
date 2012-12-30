#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	char *pwd = getenv("PWD");
	char *home = getenv("HOME");

	if (pwd != NULL)
		printf("PWD: %s\n", pwd);
	if (home != NULL)
		printf("HOME: %s\n", home);

	return 0;
}
