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
#include "real.h"

static const char real_type[] = "REAL";

#define assert_object_is_real(object) \
	if (!object_is_real(object)) \
		object_throw_bad_type(object, real_type)

static _Bool real_type_registered = false;

char *real_to_str(const real_t *real);

void real_type_register(void)
{
	type_t *type;

	if (!real_type_registered) {
		type = type_get(real_type);
		type_set_callback(type, "free", free);
		type_set_callback(type, "to_str", real_to_str);
		real_type_registered = true;
	}
}

real_t * real_new(double value)
{
	real_t *real;
	double *value_p;

	real_type_register();

	value_p = object_malloc(sizeof(double));
	*value_p = value;

	real = object_new(real_type, value_p);

	return real;
}

void real_set(real_t *real, double value)
{
	double *value_p;

	assert_object_is_real(real);

	value_p = object_value(real);
	*value_p = value;
}

double real_get(const real_t *real)
{
	double *value_p;

	assert_object_is_real(real);

	value_p = object_value(real);
	return *value_p;
}

int object_is_real(const object_t *object)
{
	if (object_isa(object, real_type))
		return 1;
	
	return 0;
}

char *real_to_str(const real_t *real)
{
	char buffer[32];

	sprintf(buffer, "%f", real_get(real));

	return object_strdup(buffer);
}
