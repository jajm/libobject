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

#ifndef object_type_h_included
#define object_type_h_included

typedef struct type_s type_t;

/* Initialize the global data structure that will handle types.
 *
 * You probably don't need to use this function, as it is called when type_get()
 * is used for the first time.
 * If already initialized, calling this function re-initialize the data
 * structure, cleaning out all registered types.
 */
void
types_initialize(void);

/* Retrieve a type by its name.
 *
 * If type doesn't exist yet, it is registered first.
 *
 * Parameters
 *   name : The unique string identifier of type to retrieve.
 *
 * Returns
 *   Pointer to type.
 */
type_t *
type_get(
	const char *name
);

/* Get the type name.
 *
 * Parameters
 *   type : Pointer to type.
 *
 * Returns
 *   The unique string identifier of the type.
 */
const char *
type_name(
	type_t *type
);

/* Register a callback for a type.
 *
 * Parameters
 *   type     : Pointer to type.
 *   name     : A unique string identifier for this callback.
 *   callback : A function pointer.
 */
void
type_set_callback(
	type_t *type,
	const char *name,
	void *callback
);

/* Retrieve a callback by its name.
 *
 * Parameters
 *   type : Pointer to type.
 *   name : The unique string identifier for the callback to retrieve.
 *
 * Returns
 *   The function pointer.
 */
void *
type_get_callback(
	type_t *type,
	const char *name
);

/* Free memory used by global data structure.
 *
 * Call it when you don't need types anymore.
 */
void
types_finalize(void);

#endif /* ! object_type_h_included */

