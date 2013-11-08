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

#ifndef object_integer_h_included
#define object_integer_h_included

#include "object.h"

typedef object_t integer_t;
typedef int integer_int_t;

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new integer.
 *
 * Parameters
 *   value : Integer value.
 *
 * Returns
 *   Pointer to integer.
 */
integer_t *
integer_new(
	integer_int_t value
);

#define integer(value) \
	integer_new(value)

/* Set the value of integer.
 *
 * Parameters
 *   integer : Pointer to integer.
 *   value   : The new integer value.
 */
void
integer_set(
	integer_t *integer,
	integer_int_t value
);

/* Get the value of integer.
 *
 * Parameters
 *   integer : Pointer to integer.
 *
 * Returns
 *   Integer value.
 */
integer_int_t
integer_get(
	const integer_t *integer
);

/* Tell if object is integer.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   0 if object is not an integer.
 *   1 if object is an integer.
 */
int
object_is_integer(
	const object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_integer_h_included */

