#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b)
{
	return strcmp(*a, *b);
}

DArray *create_words()
{
	DArray *result = DArray_create(0, 5);
	char *words[] = {"asdfasdf", "jkfd", "1234", "asdfasdf", "oioj"};
	int i;

	for (i = 0; i < 5; i++)
		DArray_push(result, words[i]);

	return result;
}

int is_sorted(DArray *array)
{
	int i;

	for (i = 0; i < DArray_count(array) - 1; i++)
		if (strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0)
			return 0;

	return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
	DArray *words = create_words();
	mu_assert(!is_sorted(words), "Words are already sorted.");

	debug("---- Testing %s sorting algorithm", name);
	
	int rc = func(words, (DArray_compare) testcmp);

	mu_assert(rc == 0, "Sort failed");
	mu_assert(is_sorted(words), "Words are not sorted");

	DArray_destroy(words);

	return NULL;
}

char *test_qsort()
{
	return run_sort_test(DArray_qsort, "qsort");
}

char * all_tests()
{
	mu_suite_start();

	mu_run_test(test_qsort);

	return NULL;
}

RUN_TESTS(all_tests)
