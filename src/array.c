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
#include <libgends/dlist.h>
#include "log.h"
#include "exception.h"
#include "type.h"
#include "object.h"
#include "malloc.h"
#include "iterator.h"
#include "utils.h"
#include "array.h"

static const char array_type[] = "ARRAY";

#define assert_object_is_array(object) \
	if (!object_is_array(object)) \
		object_throw_bad_type(object, array_type);

void array_free_callback(gds_dlist_t *list)
{
	gds_dlist_free(list, object_free, NULL);
}

static _Bool array_type_registered = false;

iterator_t * array_iterator_new(const object_t *object);
char *array_to_str(const array_t *array);
gds_dlist_t * array_copy(gds_dlist_t *value);

void array_type_register(void)
{
	type_t *type;

	if (!array_type_registered) {
		type = type_get(array_type);
		type_set_callback(type, "free", array_free_callback);
		type_set_callback(type, "iterator", array_iterator_new);
		type_set_callback(type, "to_str", array_to_str);
		type_set_callback(type, "copy", array_copy);
		array_type_registered = true;
	}
}

array_t * array_new(unsigned int size, object_t *objects[])
{
	gds_dlist_t *list;

	array_type_register();

	list = gds_dlist_new_from_array(size, (void **)objects);
	if (list == NULL) {
		log_error("List creation failed");
		return NULL;
	}

	return object_new(array_type, list);
}

void array_push(array_t *array, object_t *object)
{
	assert_object_is_array(array);

	gds_dlist_push(object_value(array), object);
}

void array_unshift(array_t *array, object_t *object)
{
	assert_object_is_array(array);

	gds_dlist_unshift(object_value(array), object);
}

object_t * array_pop(array_t *array)
{
	assert_object_is_array(array);

	return gds_dlist_pop(object_value(array));
}

object_t * array_shift(array_t *array)
{
	assert_object_is_array(array);

	return gds_dlist_shift(object_value(array));
}

object_t * array_get(const array_t *array, unsigned int offset)
{
	assert_object_is_array(array);

	return gds_dlist_get(object_value(array), offset);
}

void array_splice(array_t *array, unsigned int offset, unsigned int length,
	array_t *replacement)
{
	assert_object_is_array(array);

	if (replacement != NULL) {
		assert_object_is_array(replacement);
	}

	gds_dlist_splice(object_value(array), offset, length, object_free,
		NULL, object_value(replacement));
}

array_t * array_slice(const array_t *array, unsigned int offset,
	unsigned int length)
{
	gds_dlist_t *slice;

	assert_object_is_array(array);

	slice = gds_dlist_slice(object_value(array), offset, length, NULL,
		NULL);

	return object_new(array_type, slice);
}

void array_map(array_t *array, void *callback, void *callback_data)
{
	assert_object_is_array(array);
	gds_dlist_map(object_value(array), callback, callback_data);
}

array_t * array_filter(const array_t *array, void *callback, void *callback_data)
{
	gds_dlist_t *filtered;

	assert_object_is_array(array);

	filtered = gds_dlist_filter(object_value(array), callback,
		callback_data);
	return object_new(array_type, filtered);
}

object_t * array_reduce(const array_t *array, void *callback, void *callback_data)
{
	assert_object_is_array(array);

	return gds_dlist_reduce(object_value(array), callback, callback_data);
}

unsigned int array_size(const array_t *array)
{
	assert_object_is_array(array);

	return gds_dlist_size(object_value(array));
}

typedef struct {
	const object_t *object;
	gds_iterator_t *iterator;
} array_iterator_data_t;

int array_iterator_reset(array_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_reset(data->iterator);
	}

	return -1;
}

int array_iterator_step(array_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_step(data->iterator);
	}

	return -1;
}

object_t * array_iterator_get(array_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_get(data->iterator);
	}

	return UNDEFINED;
}

void * array_iterator_getkey(array_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_getkey(data->iterator);
	}

	return UNDEFINED;
}

void array_iterator_free(array_iterator_data_t *data)
{
	if (data != NULL) {
		gds_iterator_free(data->iterator);
		free(data);
	}
}

iterator_t * array_iterator_new(const object_t *object)
{
	array_iterator_data_t *data;
	iterator_t *iterator;

	if (!object_is_array(object)) {
		return NULL;
	}

	data = object_malloc(sizeof(array_iterator_data_t));

	data->object = object;
	data->iterator = gds_dlist_iterator_new(object_value(object));

	iterator = iterator_new(data,
		(iterator_reset_cb) array_iterator_reset,
		(iterator_step_cb) array_iterator_step,
		(iterator_get_cb) array_iterator_get,
		(iterator_getkey_cb) array_iterator_getkey,
		(iterator_free_cb) array_iterator_free
	);

	return iterator;
}

int object_is_array(const object_t *object)
{
	if (object_isa(object, array_type))
		return 1;
	
	return 0;
}

char *array_to_str(const array_t *array)
{
	char buffer[32];

	sprintf(buffer, "ARRAY(%p)", array);

	return object_strdup(buffer);
}

gds_dlist_t * array_copy(gds_dlist_t *value)
{
	gds_dlist_t *copy;
	object_t *object;

	copy = gds_dlist_new();

	gds_dlist_foreach(object, value) {
		gds_dlist_push(copy, object_copy(object));
	}

	return copy;
}
