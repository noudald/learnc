#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

inline void ListNode_swap(ListNode *a, ListNode *b)
{
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
	check(list != NULL, "encountered NULL list");
	check(cmp != NULL, "No comparisation algorithm.");

	int sorted = 1;

	if (List_count(list) <= 1)
		return 0;

	do {
		sorted = 1;

		LIST_FOREACH(list, first, next, cur)
			if (cur->next)
				if (cmp(cur->value, cur->next->value) > 0) {
					ListNode_swap(cur, cur->next);
					sorted = 0;
				}

	} while (!sorted);

	return 0;
error:
	return -1;
}

inline List *List_merge(List *left, List *right, List_compare cmp)
{
	check(left != NULL, "Encountered NULL left list");
	check(right != NULL, "Encountered NULL right list");
	check(cmp != NULL, "No comparisation algorithm");

	List *result = List_create();
	check(result != NULL, "Failed to create new list");

	void *val = NULL;

	while (List_count(left) > 0 || List_count(right) > 0) {
		if (List_count(left) > 0 && List_count(right) > 0) {
			if (cmp(List_first(left), List_first(right)) <= 0)
				val = List_shift(left);
			else
				val = List_shift(right);

			List_push(result, val);

		} else if (List_count(left) > 0) {
			val = List_shift(left);
			List_push(result, val);
		} else if (List_count(right) > 0) {
			val = List_shift(right);
			List_push(result, val);
		}
	}

	return result;
error:
	if (result)
		List_destroy(result);
	return NULL;
}

List *List_merge_sort(List *list, List_compare cmp)
{
	List *left, *right, *sort_left, *sort_right;

	check(list != NULL, "Encountered NULL list.");
	check(cmp != NULL, "No comparisation algorithm");

	
	if (List_count(list) <= 1)
		return list;

	left = List_create();
	check(left != NULL, "Could not create list");

	right = List_create();
	check(right != NULL, "Could not create list");

	int middle = List_count(list) / 2;

	LIST_FOREACH(list, first, next, cur) {
		if (middle > 0)
			List_push(left, cur->value);
		else
			List_push(right, cur->value);
		middle--;
	}

	sort_left = List_merge_sort(left, cmp);
	sort_right = List_merge_sort(right, cmp);

	if (sort_left != left)
		List_destroy(left);
	if (sort_right != right)
		List_destroy(right);

	return List_merge(sort_left, sort_right, cmp);
error:
	if (left)
		List_destroy(left);
	if (right)
		List_destroy(right);
	if (sort_left)
		List_destroy(sort_left);
	if (sort_right)
		List_destroy(sort_right);
	return NULL;
}

