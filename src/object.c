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
#include <string.h>
#include <libexception/exception.h>
#include "log.h"
#include "exception.h"
#include "type.h"
#include "malloc.h"
#include "iterator.h"
#include "object.h"

struct object_s {
	type_t *type;
	void *value;
	_Bool is_ref;
};

object_t * object_new(const char *type, void *value)
{
	object_t *object = NULL;

	if (type == NULL) {
		log_error("type cannot be NULL");
		return NULL;
	}

	object = object_malloc(sizeof(object_t));

	object->type = type_get(type);
	object->value = value;
	object->is_ref = false;

	return object;
}

object_t * object_new_ref(const char *type, void *value)
{
	object_t *ref;

	ref = object_malloc(sizeof(object_t));

	ref->type = type_get(type);
	ref->value = value;
	ref->is_ref = true;

	return ref;
}

object_t * object_get_ref(object_t *object)
{
	object_t *ref;

	ref = object_malloc(sizeof(object_t));

	ref->type = object->type;
	ref->value = object->value;
	ref->is_ref = true;

	return ref;
}

const char * object_type(const object_t *object)
{
	const char *type = NULL;

	if (object_isset(object)) {
		type = type_name(object->type);
	}

	return type;
}

void * object_value(const object_t *object)
{
	void *value = NULL;

	if (object != NULL) {
		value = object->value;
	}

	return value;
}

void object_set(object_t *object, void *value)
{
	if (object != NULL) {
		object->value = value;
	}
}

int object_isset(const object_t *object)
{
	if (object != NULL && object->type != NULL)
		return 1;

	return 0;
}

int object_isa(const object_t *object, const char *type)
{
	const char *typename;

	if (object_isset(object)) {
		typename = type_name(object->type);
		if (type == typename || !strcmp(typename, type))
			return 1;
	}

	return 0;
}

iterator_t * object_iterator_new(const object_t *object)
{
	iterator_t *(*iterator_callback)(const object_t *);
	iterator_t *iterator = NULL;

	if (object_isset(object)) {
		iterator_callback = type_get_callback(object->type, "iterator");
		if (iterator_callback != NULL) {
			iterator = iterator_callback(object);
		}
	}

	return iterator;
}

char * object_to_str(const object_t *object)
{
	char *(*to_str_callback)(const object_t *);
	char *str = NULL;

	if (object_isset(object)) {
		to_str_callback = type_get_callback(object->type, "to_str");
		if (to_str_callback != NULL) {
			str = to_str_callback(object);
		}
	}

	return str;
}

void object_free_value(object_t *object)
{
	void (*free_callback)(void *);

	free_callback = type_get_callback(object->type, "free");
	if (free_callback != NULL) {
		free_callback(object->value);
	}
}

void object_free(object_t *object)
{
	if (object_isset(object) && !object->is_ref) {
		object_free_value(object);
	}
	free(object);
}
