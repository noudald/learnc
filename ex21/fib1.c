#include <stdio.h>

int main()
{
	long a = 0;
	long b = 1;
	unsigned long i;

	for (i = 0; i < 100000000; i++) {
		a ^= b;
		b ^= a;
		a ^= b;
		b += a;
	}

	printf("%d\n", b);

	return 0;
}
