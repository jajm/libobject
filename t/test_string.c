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
	plan(10);
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

	string_t *string3 = string_new_static("Static string");
	string_eq(string3, "Static string");
	string_len_is(string3, 13);

	string_free(string);
	string_free(string2);
	string_free(string3);

	types_finalize();

	return 0;
}
