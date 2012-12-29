#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <lcthw/dbg.h>
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message) if (!(test)) { \
	log_err(message); return message; \
}

#define mu_run_test(test) debug("\n----- TESTING %s", #test); \
	message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
	argc = 1; \
	tests_run = 0; \
	debug("----- RUNNING ALL TESTS OF: %s", argv[0]);\
	printf("----\nRUNNING ALL TESTS OF: %s\n", argv[0]);\
	char *result = name();\
	if (result != NULL) {\
    		printf("FAILED: %s\n", result);\
	} else {\
    		printf("ALL TESTS PASSED\n");\
	}\
	printf("Tests run: %d\n", tests_run);\
	exit (result != 0);\
}


int tests_run;

#endif
