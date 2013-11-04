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

#ifndef object_boolean_h_included
#define object_boolean_h_included

#include <stdbool.h>
#include "object.h"

typedef object_t boolean_t;

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new boolean object.
 *
 * Parameters
 *   value : Boolean value.
 *
 * Returns
 *   Pointer to new boolean object.
 */
boolean_t *
boolean_new(
	_Bool value
);

#define boolean(value) \
	boolean_new(value)

/* Get boolean value.
 *
 * Parameters
 *   boolean : Pointer to boolean object.
 *
 * Returns:
 *   Boolean value.
 */
_Bool
boolean_get(
	const boolean_t *boolean
);

/* Set boolean value.
 *
 * Parameters
 *   boolean : Pointer to boolean object.
 *   value   : Boolean value.
 */
void
boolean_set(
	boolean_t *boolean,
	_Bool value
);

/* Free memory used by boolean object.
 *
 * Parameters
 *   boolean : Pointer to boolean object.
 */
void
boolean_free(
	boolean_t *boolean
);

/* Determines if an object is a boolean object.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   0 if object is not a boolean object.
 *   1 if object is a boolean object.
 */
int
object_is_boolean(
	const object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_boolean_h_included */

