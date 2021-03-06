#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "string.h"
#include "type.h"
#include "foreach.h"
#include "tap.h"

int main()
{
	array_t *a;
	string_t *s;
	int i = 0;

	plan(15);

	a = array();
	ok(object_is_array(a), "object is array");
	ok(array_size(a) == 0, "array has 0 elements");

	array_push(a, string("one"));
	array_push(a, string("two"));
	ok(array_size(a) == 2, "array has 2 elements");

	array_unshift(a, string("zero"));
	ok(array_size(a) == 3, "array has 3 elements");

	foreach(a, o) {
		if (i == 0) { str_eq(string_to_c_str(o), "zero"); }
		else if (i == 1) { str_eq(string_to_c_str(o), "one"); }
		else if (i == 2) { str_eq(string_to_c_str(o), "two"); }
		i++;
	}

	s = array_pop(a);
	str_eq(string_to_c_str(s), "two");
	object_free(s);
	ok(array_size(a) == 2, "array has 2 elements");

	s = array_shift(a);
	str_eq(string_to_c_str(s), "zero");
	object_free(s);
	ok(array_size(a) == 1, "array has 1 element");

	object_free(a);

	a = object_new(NULL, NULL);
	ok(!object_is_array(a), "object is not an array");
	object_free(a);

	a = object_new("array", NULL);
	ok(!object_is_array(a), "object is not an array");
	object_free(a);

	a = object_new("ARRAY", NULL);
	ok(object_is_array(a), "object is array");
	object_free(a);

	a = array();
	char *str = object_to_str(a);
	ok(!strncmp(str, "ARRAY(", 6), "object_to_str returns \"ARRAY(...)\"");
	free(str);
	object_free(a);

	types_finalize();

	return 0;
}
