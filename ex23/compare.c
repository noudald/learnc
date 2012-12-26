#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

const int SIZE = 100000;
const int TESTS = 100000;

double get_time()
{
	struct timeval t;
	struct timezone tzp;

	gettimeofday(&t, &tzp);

	return t.tv_sec + t.tv_usec*1e-6;
}

int main()
{
	char array1[SIZE];
	char array2[SIZE];
	char temp[SIZE];
	int i;
	double t1, t2;

	memset(array1, 'x', SIZE);
	memset(array2, 'y', SIZE);

	printf("Test memset:\n");
	t1 = get_time();
	for (i = 0; i < TESTS; i++) {
		memset(array1, 'y', SIZE);
		memset(array2, 'x', SIZE);
		memset(array1, 'x', SIZE);
		memset(array2, 'y', SIZE);
	}
	t2 = get_time();
	printf("Time passed: %f\n", t2 - t1);

	printf("Test memcpy:\n");
	t1 = get_time();
	for (i = 0; i < TESTS; i++) {
		memcpy(temp, array1, SIZE);
		memcpy(array1, array2, SIZE);
		memcpy(array2, array1, SIZE);
		memcpy(temp, array1, SIZE);
		memcpy(array1, array2, SIZE);
		memcpy(array2, array1, SIZE);
	}
	t2 = get_time();
	printf("Time passed: %f\n", t2 - t1);

	printf("Test memmove:\n");
	t1 = get_time();
	for (i = 0; i < TESTS; i++) {
		memmove(temp, array1, SIZE);
		memmove(array2, array1, SIZE);
		memmove(array1, temp, SIZE);
		memmove(temp, array1, SIZE);
		memmove(array2, array1, SIZE);
		memmove(array1, temp, SIZE);
	}
	t2 = get_time();
	printf("Time passed: %f\n", t2 - t1);

	return 0;
}
