#undef NDEBUG
#include "../ex20/dbg.h"
#include <stdio.h>
#include <assert.h>

void copy(char to[], char from[])
{
	int i = 0;

	while((to[i] = from[i]) != '\0')
		i++;
}

int safer_copy(char *from, int from_len, char *to, int to_len)
{
	assert(from != NULL && to != NULL && "from or to can't be NULL");

	int i = 0;
	int max = from_len > to_len -1 ? to_len - 1 : from_len;

	if (from_len < 0 || to_len <= 0)
		return -1;

	for (i = 0; i < max; i++)
		to[i] = from[i];

	to[to_len - 1] = '\0';

	return i;
}

int main(int argc, char *argv[])
{
	char from[] = "0123456789";
	int from_len = sizeof(from);

	char to[] = "01234567";
	int to_len = sizeof(to);

	debug("Copying '%s':%d to '%s':%d", from, from_len, to, to_len);

	int rc = safer_copy(from, from_len, to, to_len);
	check(rc > 0, "Failed to safer_copy.");
	check(to[to_len - 1] == '\0', "String not terminated.");

	debug("Result is '%s':%d", to, to_len);

	rc = safer_copy(from, from_len*(-1), to, to_len);
	check(rc == -1, "safer_copy should fail #1");
	check(to[to_len - 1] == '\0', "String not terminated.");

	debug("Result is '%s':%d", to, to_len);

	rc = safer_copy(from, from_len, to, 0);
	check(rc == -1, "safer_copy sould fail #2");
	check(to[to_len - 1] == '\0', "String not terminated.");
	
	debug("Result is '%s':%d", to, to_len);

	return 0;
error:
	return 1;
}
