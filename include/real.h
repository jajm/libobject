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

#ifndef object_real_h_included
#define object_real_h_included

#include "object.h"

typedef object_t real_t;

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new real.
 *
 * Parameters
 *   value : Real value.
 *
 * Returns
 *   Pointer to real.
 */
real_t *
real_new(
	double value
);

#define real(value) \
	real_new(value)

/* Set real value.
 *
 * Parameters
 *   real  : Pointer to real.
 *   value : New real value.
 */
void
real_set(
	real_t *real,
	double value
);

/* Get real value.
 *
 * Parameters
 *   real : Pointer to real.
 *
 * Returns
 *   Real value.
 */
double
real_get(
	const real_t *real
);

/* Tell if object is real.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns:
 *   0 if object is not real.
 *   1 if object is real.
 */
int
object_is_real(
	const object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_real_h_included */

