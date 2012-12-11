#include <stdio.h>

/*
 * SHRT_MAX	= 32767 = 2^15 - 1
 * USHRT_MAX	= 65535 = 2^16 - 1
 * INT_MAX	= 2147483647 = 2^31 - 1
 * UINT_MAX	= 4294967295 = 2^32 - 1
 * LONG_MAX	= 9223372036854775807 = 2^63 - 1
 * ULONG_MAX	= 18446744073709551615 = 2^64 - 1
 */

int main(int argc, char * argv[])
{
	int bugs = 100;
	double bug_rate = 1.2;

	printf("You have %d bugs at the imaginary rate of %f.\n",
		bugs, bug_rate);

	long universe_of_defects = 1L * 1024L * 1024L * 1024L;
	printf("The entire universe had %ld bugs.\n",
		universe_of_defects);

	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", expected_bugs);
	
	double part_of_universe = expected_bugs / universe_of_defects;
	printf("That is only a %e portion of the universe.\n",
		part_of_universe);

	char nul_byte = '\0';
	int care_percentage = bugs * nul_byte;
	printf("Which means you should care %d%%.\n", care_percentage);

	return 0;
}
