#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "exception.h"
#include "type.h"
#include "object.h"
#include "boolean.h"

static const char boolean_type[] = "BOOLEAN";

#define assert_object_is_boolean(object) \
	if (!object_is_boolean(object)) \
		object_throw_bad_type(object, boolean_type)

static _Bool boolean_type_registered = false;

void boolean_type_register(void)
{
	if (!boolean_type_registered) {
		type_get(boolean_type);
		boolean_type_registered = true;
	}
}

static _Bool boolean_true = true;
static _Bool boolean_false = false;

boolean_t * boolean_new(_Bool value)
{
	_Bool *value_p;

	boolean_type_register();

	value_p = value ? &boolean_true : &boolean_false;

	return object_new(boolean_type, value_p);
}

_Bool boolean_get(const boolean_t *boolean)
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
	assert_object_is_boolean(boolean);
	object_free(boolean);
}

int object_is_boolean(const object_t *object)
{
	if (object_isa(object, boolean_type))
		return 1;

	return 0;
}
