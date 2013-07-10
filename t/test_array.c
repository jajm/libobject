#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "array_iterator.h"
#include "string.h"

int tests_failed = 0;

#define ok(test) \
	if (!(test)) { \
		tests_failed ++; \
		printf("Test failed at line %d: %s\n", __LINE__, #test); \
	}

#define str_eq(got, expected) \
	ok(strcmp(string_to_c_str(got), expected) == 0)

int main()
{
	array_t *a;
	string_t *s;
	int i = 0;

	a = array();
	ok(object_is_array(a));
	ok(array_size(a) == 0);

	array_push(a, string("one"));
	array_push(a, string("two"));
	ok(array_size(a) == 2);

	array_unshift(a, string("zero"));
	ok(array_size(a) == 3);

	array_foreach(a, o) {
		if (i == 0) { str_eq(o, "zero"); }
		else if (i == 1) { str_eq(o, "one"); }
		else if (i == 2) { str_eq(o, "two"); }
		i++;
	}

	s = array_pop(a);
	str_eq(s, "two");
	string_free(s);
	ok(array_size(a) == 2);

	s = array_shift(a);
	str_eq(s, "zero");
	string_free(s);
	ok(array_size(a) == 1);

	array_free(a, string_free, NULL);

	a = object_new("", NULL);
	ok(!object_is_array(a));
	object_free(a, NULL, NULL);

	a = object_new("array", NULL);
	ok(!object_is_array(a));
	object_free(a, NULL, NULL);

	a = object_new("ARRAY", NULL);
	ok(object_is_array(a));
	array_free(a, NULL, NULL);

	if (tests_failed == 0) {
		printf("All tests pass!\n");
	}

	return tests_failed;
}
