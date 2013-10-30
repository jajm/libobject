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

array_t *
array_new(
	unsigned int size,
	object_t *values[]
);

#define array(...) ({ \
	object_t *__values[] = {__VA_ARGS__}; \
	array_new(sizeof(__values) / sizeof(object_t *), __values); \
})

void
array_push(
	array_t *array,
	object_t *object
);

void
array_unshift(
	array_t *array,
	object_t *object
);

object_t *
array_pop(
	array_t *array
);

object_t *
array_shift(
	array_t *array
);

object_t *
array_get(
	const array_t *array,
	unsigned int offset
);

void
array_splice(
	array_t *array,
	unsigned int offset,
	unsigned int length,
	void *callback,
	void *callback_data,
	array_t *replacement
);

array_t *
array_slice(
	const array_t *array,
	unsigned int offset,
	unsigned int length,
	void *callback,
	void *callback_data
);

void
array_map(
	array_t *array,
	void *callback,
	void *callback_data
);

array_t *
array_filter(
	const array_t *array,
	void *callback,
	void *callback_data
);

object_t *
array_reduce(
	const array_t *array,
	void *callback,
	void *callback_data
);

unsigned int
array_size(
	const array_t *array
);

iterator_t *
array_iterator_new(
	const object_t *object
);


#define array_foreach(array, object) \
	for (iterator_t *__it = array_iterator_new(array) \
		; __it != NULL \
		; iterator_free(__it), __it = NULL) \
	while (!iterator_step(__it)) \
	for (object_t *object = iterator_get(__it), *__b = 0; __b == 0; \
		__b = (object_t *)1)

void array_free(
	array_t *array
);

int
object_is_array(
	const object_t *object
);

#endif /* ! object_array_h_included */

