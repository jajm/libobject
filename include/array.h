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

#ifndef object_array_h_included
#define object_array_h_included

#include "object.h"
#include "iterator.h"

typedef object_t array_t;

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new array.
 *
 * Parameters
 *   size   : size of values
 *   values : an array of objects to insert in the new array.
 *
 * Returns
 *   Pointer to the new array.
 */
array_t *
array_new(
	unsigned int size,
	object_t *values[]
);

#define array(...) ({ \
	object_t *__values[] = {__VA_ARGS__}; \
	array_new(sizeof(__values) / sizeof(object_t *), __values); \
})

/* Add an object at the end of array.
 *
 * Parameters
 *   array  : Pointer to array.
 *   object : Pointer to object.
 */
void
array_push(
	array_t *array,
	object_t *object
);

/* Add an object at the beginning of array.
 *
 * Parameters
 *   array  : Pointer to array.
 *   object : Pointer to object.
 */
void
array_unshift(
	array_t *array,
	object_t *object
);

/* Remove the last element of array.
 *
 * Parameters
 *   array : Pointer to array.
 *
 * Returns
 *   The removed object.
 */
object_t *
array_pop(
	array_t *array
);

/* Remove the first element of array.
 *
 * Parameters
 *   array : Pointer to array.
 *
 * Returns
 *   The removed object.
 */
object_t *
array_shift(
	array_t *array
);

/* Retrieve an element at specified offset in array.
 *
 * Parameters
 *   array  : Pointer to array.
 *   offset : Offset of element to retrieve (first element is at offset 0).
 *
 * Returns
 *   Pointer to object at specified offset,
 *   or NULL if there is nothing at this offset.
 */
object_t *
array_get(
	const array_t *array,
	unsigned int offset
);

/* Remove a portion of elements and replace them by elements in another array.
 *
 * Parameters
 *   array       : Pointer to array.
 *   offset      : Where to start removal.
 *   length      : Number of elements to remove.
 *   replacement : Pointer to array which contains elements to insert.
 */
void
array_splice(
	array_t *array,
	unsigned int offset,
	unsigned int length,
	array_t *replacement
);

/* Remove a portion of elements and return an array containing them.
 *
 * Parameters
 *   array  : Pointer to array.
 *   offset : Where to start removal.
 *   length : Number of elements to remove.
 *
 * Returns
 *   A new array containing the removed elements.
 */
array_t *
array_slice(
	const array_t *array,
	unsigned int offset,
	unsigned int length
);

/* Apply a callback to each element of array.
 *
 * Parameters
 *   array         : Pointer to array.
 *   callback      : Callback called on each element. Prototype should be:
 *                   void callback(object_t *object, void *data);
 *   callback_data : Data passed to callback as second parameter.
 */
void
array_map(
	array_t *array,
	void *callback,
	void *callback_data
);

/* Create a new array by filtering another array.
 *
 * Parameters
 *   array         : Pointer to array.
 *   callback      : Filter callback called on each element. Prototype should
 *                   be:
 *                   int callback(const object_t *object, void *data);
 *                   It should returns 0 if object should not be in returned
 *                   array. Any other return value will be considered as true,
 *                   and thus the object will be in returned array.
 *   callback_data : Data passed to callback as second parameter.
 */
array_t *
array_filter(
	const array_t *array,
	void *callback,
	void *callback_data
);

/* Reduce an array to a single object.
 *
 * Parameters
 *   array         : Pointer to array.
 *   callback      : Callback called on each element. Prototype should be:
 *                   object_t * callback(object_t *previous, object_t *current,
 *                       unsigned int offset, void *data);
 *                   previous is the return value of previous call of callback,
 *                   or NULL if this is the first call.
 *                   current is the current object.
 *                   offset is the offset of current object in array.
 *                   This callback should reduce previous and current into a
 *                   single object and return this object.
 *   callback_data : Data passed to callback as fourth parameter.
 */
object_t *
array_reduce(
	const array_t *array,
	void *callback,
	void *callback_data
);

/* Get the size of array.
 *
 * Parameters
 *   array: Pointer to array.
 *
 * Returns
 *   Size of array (number of elements).
 */
unsigned int
array_size(
	const array_t *array
);

/* Tell if object is an array.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   0 if object is not an array.
 *   1 if object is an array.
 */
int
object_is_array(
	const object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_array_h_included */

