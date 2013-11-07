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
#include "object.h"
#include "utils.h"
#include "boolean.h"

static const char boolean_type[] = "BOOLEAN";

#define assert_object_is_boolean(object) \
	if (!object_is_boolean(object)) \
		object_throw_bad_type(object, boolean_type)

static _Bool boolean_type_registered = false;

char *boolean_to_str(const object_t *object);

void boolean_type_register(void)
{
	type_t *type;

	if (!boolean_type_registered) {
		type = type_get(boolean_type);
		type_set_callback(type, "to_str", boolean_to_str);
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

int object_is_boolean(const object_t *object)
{
	if (object_isa(object, boolean_type))
		return 1;

	return 0;
}

char *boolean_to_str(const boolean_t *boolean)
{
	_Bool *value_p;
	char *s;

	value_p = object_value(boolean);
	s = object_strdup( (*value_p) ? "TRUE" : "FALSE" );

	return s;
}
