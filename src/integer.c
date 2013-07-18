#include <stdio.h>
#include <stdlib.h>
#include "exception.h"
#include "object.h"
#include "integer.h"

static const char integer_type[] = "INTEGER";

#define assert_object_is_integer(object) \
	if (!object_is_integer(object)) \
		object_throw_bad_type(object, integer_type)

integer_t * integer_new(integer_int_t value)
{
	integer_t *integer;
	integer_int_t *value_p;

	value_p = malloc(sizeof(integer_int_t));
	if (value_p == NULL) {
		object_throw_malloc_error(sizeof(integer_int_t));
	}
	*value_p = value;

	integer = object_new(integer_type, value_p);
	return integer;
}

void integer_set(integer_t *integer, integer_int_t value)
{
	integer_int_t *value_p;

	assert_object_is_integer(integer);

	value_p = object_value(integer);
	*value_p = value;
}

integer_int_t integer_get(integer_t *integer)
{
	integer_int_t *value_p;

	assert_object_is_integer(integer);

	value_p = object_value(integer);
	return *value_p;
}

void integer_free(integer_t *integer)
{
	if (object_is_integer(integer)) {
		object_free(integer, free, NULL);
	}
}

int object_is_integer(object_t *object)
{
	if (object_isa(object, integer_type))
		return 1;
	
	return 0;
}
