#include <stdio.h>
#include <stdlib.h>
#include "exception.h"
#include "object.h"
#include "boolean.h"

static const char boolean_type[] = "BOOLEAN";

#define assert_object_is_boolean(object) \
	if (!object_is_boolean(object)) \
		object_throw_bad_type(object, boolean_type)

boolean_t * boolean_new(_Bool value)
{
	_Bool *value_p;

	value_p = malloc(sizeof(_Bool));
	if (value_p == NULL) {
		object_throw_malloc_error(sizeof(_Bool));
	}
	*value_p = value;

	return object_new(boolean_type, value_p);
}

_Bool boolean_get(boolean_t *boolean)
{
	_Bool *value_p;

	assert_object_is_boolean(boolean);

	value_p = object_value(boolean);
	return *value_p;
}

void boolean_set(boolean_t *boolean, _Bool value)
{
	_Bool *value_p;

	assert_object_is_boolean(boolean);

	value_p = object_value(boolean);
	*value_p = value;
}

void boolean_free(boolean_t *boolean)
{
	if (object_is_boolean(boolean)) {
		object_free(boolean, free, NULL);
	}
}

int object_is_boolean(object_t *object)
{
	if (object_isa(object, boolean_type))
		return 1;

	return 0;
}
