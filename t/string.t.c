#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "type.h"
#include "tap.h"

#define string_eq(string, str) \
	str_eq(string_to_c_str(string), str)

#define string_len_is(string, len) \
	ok(string_length(string) == len, "string length is %d (got: %d)", len, string_length(string))

int main()
{
	plan(17);
	int added;

	string_t *string = string("hello", ", ", "world!");
	string_eq(string, "hello, world!");
	string_len_is(string, 13);

	added = string_cat(string, "foo", "bar", "baz");
	ok(added == 9, "string_cat added 9 characters");
	string_eq(string, "hello, world!foobarbaz");
	string_len_is(string, 22);

	string_t *string2 = string("goodbye", ", ", "world...");
	added = string_scat(string, string2);
	ok(added == 17, "string_scat added 17 characters");
	string_eq(string, "hello, world!foobarbazgoodbye, world...");
	string_len_is(string, 39);

	char *s = malloc(sizeof(char) * 12);
	strcpy(s, "foo bar baz");
	string_t *string3 = string_new_nocopy(s);
	string_eq(string3, "foo bar baz");
	string_len_is(string3, 11);

	char *str = object_to_str(string3);
	ok(!strcmp(str, "foo bar baz"), "object_to_str returns \"foo bar baz\"");
	free(str);

	string_t *string4 = string_new_from_substring("foo, bar, baz", 3, 6);
	string_eq(string4, ", bar,");

	string_t *string5 = string_substring(string3, 4, 3);
	string_eq(string5, "bar");

	string_t *string6 = string("foo,bar,baz");
	array_t *array1 = string_split(string6, ',');
	iterator_t *it = object_iterator_new(array1);
	iterator_reset(it);
	iterator_step(it);
	string_eq(iterator_get(it), "foo");
	iterator_step(it);
	string_eq(iterator_get(it), "bar");
	iterator_step(it);
	string_eq(iterator_get(it), "baz");
	ok(0 < iterator_step(it), NULL);
	iterator_free(it);

	object_free(string);
	object_free(string2);
	object_free(string3);
	object_free(string4);
	object_free(string5);
	object_free(string6);
	object_free(array1);

	types_finalize();

	return 0;
}
