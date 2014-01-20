/*
 * Copyright 2013 Julian Maurice
 *
 * This file is part of libobject
 *
 * libobject is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libobject is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libobject.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "exception.h"
#include "type.h"
#include "malloc.h"
#include "object.h"
#include "utils.h"
#include "integer.h"

static const char integer_type[] = "INTEGER";

#define assert_object_is_integer(object) \
	if (!object_is_integer(object)) \
		object_throw_bad_type(object, integer_type)

static _Bool integer_type_registered = false;

char *integer_to_str(const integer_t *integer);
integer_int_t * integer_copy(const integer_int_t *value);

void integer_type_register(void)
{
	type_t *type;

	if (!integer_type_registered) {
		type = type_get(integer_type);
		type_set_callback(type, "free", free);
		type_set_callback(type, "to_str", integer_to_str);
		type_set_callback(type, "copy", integer_copy);
		integer_type_registered = true;
	}
}

integer_t * integer_new(integer_int_t value)
{
	integer_t *integer;
	integer_int_t *value_p;

	integer_type_register();

	value_p = object_malloc(sizeof(integer_int_t));
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

integer_int_t integer_get(const integer_t *integer)
{
	integer_int_t *value_p;

	assert_object_is_integer(integer);

	value_p = object_value(integer);
	return *value_p;
}

int object_is_integer(const object_t *object)
{
	if (object_isa(object, integer_type))
		return 1;
	
	return 0;
}

char *integer_to_str(const integer_t *integer)
{
	char buffer[32];
	integer_int_t *value_p;

	value_p = object_value(integer);
	sprintf(buffer, "%d", *value_p);

	return object_strdup(buffer);
}

integer_int_t * integer_copy(const integer_int_t *value)
{
	integer_int_t *copy;

	copy = object_malloc(sizeof(integer_int_t));
	*copy = *value;

	return copy;
}
