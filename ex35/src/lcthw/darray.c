#include <lcthw/darray.h>
#include <assert.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
	DArray *new_array = malloc(sizeof(DArray));
	check_mem(new_array);

	new_array->max = initial_max;
	check(new_array->max > 0, "You must set an initial_max > 0.");

	new_array->contents = calloc(initial_max, sizeof(void *));
	check_mem(new_array->contents);

	new_array->end = 0;
	new_array->element_size = element_size;
	new_array->expand_rate = DEFAULT_EXPAND_RATE;

	return new_array;
error:
	if (new_array)
		free(new_array);
	return NULL;	
}

void DArray_destroy(DArray *array)
{
	if (array) {
		if (array->contents)
			free(array->contents);
		free(array);
	}
}

void DArray_clear(DArray *array)
{
	check(array != NULL, "Encountered NULL array, nothing to clear.");

	int i;

	if (array->element_size > 0)
		for (i = 0; i < array->max; i++)
			if (array->contents[i] != NULL)
				free(array->contents[i]);

error:
	return;
}

static inline int DArray_resize(DArray *array, size_t newsize)
{
	array->max = newsize;
	check(array->max > 0, "The newsize must be > 0.");

	void *contents = realloc(array->contents, array->max * sizeof(void *));
	check_mem(contents);

	array->contents = contents;

	return 0;
error:
	if (contents)
		free(contents);
	return -1;
}

int DArray_expand(DArray *array)
{
	size_t old_max = array->max;
	int rc = DArray_resize(array, array->max + array->expand_rate);
	check(rc == 0, "Failed to expand array to new size %d",
		array->max + (int)array->expand_rate);

	memset(array->contents + old_max, 0, array->expand_rate + 1);
	return 0;
error:
	return -1;
}

int DArray_contract(DArray *array)
{
	int new_size;

	if (array->end < (int)array->expand_rate)
		new_size = (int)array->expand_rate;
	else
		new_size = array->end;

	return DArray_resize(array, new_size + 1);
}

int DArray_push(DArray *array, void *el)
{
	array->contents[array->end] = el;
	array->end++;

	if (DArray_end(array) >= DArray_max(array))
		return DArray_expand(array);
	else
		return 0;
}

void *DArray_pop(DArray *array)
{

	check(array->end > 0, "Empty array.");

	void *el = DArray_remove(array, array->end - 1);
	array->end--;

	if (DArray_end(array) > (int)array->expand_rate
			&& DArray_end(array) % array->expand_rate)
		DArray_contract(array);

	return el;
error:
	return NULL;
}

void DArray_clear_destroy(DArray *array)
{
	DArray_clear(array);
	DArray_destroy(array);
}
