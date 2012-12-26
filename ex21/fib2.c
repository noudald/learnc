#include <stdio.h>

int main()
{
	register long a = 0;
	register long b = 1;
	register unsigned long i;

	for (i = 0; i < 100000000; i++) {
		a ^= b;
		b ^= a;
		a ^= b;
		b += a;
	}

	printf("%d\n", b);

	return 0;
}
