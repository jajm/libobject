#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

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
	char *s = "Hello, object world";
	char *s2 = "Hello again, world";
	const char *string_type = "STRING";
	const char *string_type2 = "string";

	o = object_new(string_type, s);
	ok(o != NULL);
	ok(object_isset(o));
	str_eq(object_type(o), string_type);
	ok(object_type(o) != string_type);
	str_eq(object_value(o), s);
	ok(object_value(o) == s);

	ok(0 == object_set(o, string_type2, s2));
	ok(object_isset(o));
	str_eq(object_type(o), string_type2);
	ok(object_type(o) != string_type2);
	str_eq(object_value(o), s2);
	ok(object_value(o) == s2);

	object_unset(o, NULL, NULL);
	ok(object_isset(o) == 0);
	str_eq(object_type(o), "");
	ok(object_value(o) == NULL);

	object_free(o, NULL, NULL);
	ok(object_isset(NULL) == 0);

	if (tests_failed == 0) {
		printf("All tests pass!\n");
	}

	return tests_failed;
}
