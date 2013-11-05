#include <stdlib.h>
#include <stdio.h>
#include "integer.h"
#include "type.h"
#include "tap.h"

int main()
{
	integer_t *integer;

	plan(4);

	integer = integer_new(42);
	ok(42 == integer_get(integer), "integer_get(integer_new(42)) == 42");
	integer_set(integer, 21);
	ok(21 == integer_get(integer), "integer_set(integer, 21); integer_get(integer) == 21");
	ok(object_is_integer(integer), "object_is_integer(integer)");

	char *str = object_to_str(integer);
	ok(!strcmp(str, "21"), "object_to_str returns \"21\"");
	free(str);

	integer_free(integer);

	types_finalize();

	return 0;
}
