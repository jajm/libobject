#include <stdio.h>
#include "integer.h"

int main()
{
	integer_t *integer;

	integer = integer_new(42);
	printf("42 = %d\n", integer_get(integer));
	integer_set(integer, 21);
	printf("21 = %d\n", integer_get(integer));
	printf("is_integer = %d\n", object_is_integer(integer));
	integer_free(integer);

	return 0;
}
