#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

int tests_failed = 0;

#define ok(test) \
	if (!(test)) { \
		tests_failed ++; \
		printf("Test failed at line %d: %s\n", __LINE__, #test); \
	}

#define str_eq(got, expected) \
	ok(strcmp(got, expected) == 0)

int main()
{
	object_t *o;

	o = array();
	ok(object_is_array(o));
	ok(array_size(o) == 0);

	array_push(o, "one");
	array_push(o, "two");
	ok(array_size(o) == 2);

	array_unshift(o, "zero");
	ok(array_size(o) == 3);

	str_eq(array_pop(o), "two");
	ok(array_size(o) == 2);

	str_eq(array_shift(o), "zero");
	ok(array_size(o) == 1);

	array_free(o, NULL, NULL);

	o = object_new("", NULL);
	ok(!object_is_array(o));

	o = object_new("array", NULL);
	ok(!object_is_array(o));

	o = object_new("ARRAY", NULL);
	ok(object_is_array(o));

	if (tests_failed == 0) {
		printf("All tests pass!\n");
	}

	return tests_failed;
}
