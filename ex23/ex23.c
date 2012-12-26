/* Duff's device */

#include <stdio.h>
#include <string.h>
#include "../ex20/dbg.h"

int normal_copy(char *from, char *to, int count)
{
	int i = 0;

	for (i = 0; i < count; i++)
		to[i] = from[i];

	return i;
}

int duffs_device(char *from, char *to, int count)
{
	{
		int n = (count + 7) / 8;

		switch (count % 8) {
			case 0: do {
				*to++ = *from++;
				case 7: *to++ = *from++;
				case 6: *to++ = *from++;
				case 5: *to++ = *from++;
				case 4: *to++ = *from++;
				case 3: *to++ = *from++;
				case 2: *to++ = *from++;
				case 1: *to++ = *from++;
			} while (--n > 0);
		}
	}

	return count;
}

int zeds_device(char *from, char *to, int count)
{
	{
		int n = (count + 7) / 8;

		switch (count % 8) {
			case 0:
			again: *to++ = *from++;
			case 7: *to++ = *from++;
			case 6: *to++ = *from++;
			case 5: *to++ = *from++;
			case 4: *to++ = *from++;
			case 3: *to++ = *from++;
			case 2: *to++ = *from++;
			case 1: *to++ = *from++;
				if (--n > 0) goto again;
		}
	}

	return count;
}

int valid_copy(char *data, int count, char expects)
{
	int i = 0;
	for (i = 0; i < count; i++) {
		if (data[i] != expects) {
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	char from[10] = {'a'};
	char to[10] = {'c'};
	int rc = 0;

	memset(from, 'x', 10);
	memset(to, 'y', 10);
	check(valid_copy(to, 10, 'y'), "Not initialized right.");

	rc = normal_copy(from, to, 10);
	check(rc == 10, "Normal copy failed: %d", rc);
	check(valid_copy(to, 10, 'x'), "Normal copy failed.");

	memset(to, 'y', 10);
	rc = duffs_device(from, to, 10);
	check(rc == 10, "Duff's device failed: %d", rc);
	check(valid_copy(to, 10, 'x'), "Duff's device failed copy.");

	memset(to, 'y', 10);
	rc = zeds_device(from, to, 10);
	check(rc == 10, "Zed's device failed: %d", rc);
	check(valid_copy(to, 10, 'x'), "Zed's device failed copy.");

	return 0;
error:
	return 1;
}
