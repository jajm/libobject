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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "malloc.h"
#include "json.h"
#include "object.h"
#include "hash.h"
#include "array.h"
#include "integer.h"
#include "real.h"
#include "boolean.h"

object_t * object_from_json_object(struct json_object *json_object);

hash_t * hash_from_json_object(struct json_object *json_object)
{
	struct json_object_iterator it, it_end;
	hash_t *hash;

	it = json_object_iter_begin(json_object);
	it_end = json_object_iter_end(json_object);
	hash = hash_new();

	while (!json_object_iter_equal(&it, &it_end)) {
		const char *name = json_object_iter_peek_name(&it);
		struct json_object *value = json_object_iter_peek_value(&it);
		hash_set(hash, name, object_from_json_object(value));
		json_object_iter_next(&it);
	}

	return hash;
}

array_t * array_from_json_object(struct json_object *json_object)
{
	array_t *array;
	struct array_list *array_list;
	int length;
	int idx;

	array = array();
	array_list = json_object_get_array(json_object);
	length = array_list_length(array_list);
	idx = 0;
	while (idx < length) {
		struct json_object *value = array_list_get_idx(array_list, idx);
		array_push(array, object_from_json_object(value));
		idx++;
	}

	return array;
}

string_t * string_from_json_object(struct json_object *json_object)
{
	string_t *string;
	const char *value;

	value = json_object_get_string(json_object);
	string = string(value);

	return string;
}

object_t * object_from_json_object(struct json_object *json_object)
{
	object_t *object;
	enum json_type type;

	type = json_object_get_type(json_object);
	switch (type) {
		case json_type_null:
			object = NULL;
			break;
		case json_type_boolean:
			object = boolean_new(json_object_get_boolean(json_object));
			break;
		case json_type_double:
			object = real_new(json_object_get_double(json_object));
			break;
		case json_type_int:
			object = integer_new(json_object_get_int(json_object));
			break;
		case json_type_object:
			object = hash_from_json_object(json_object);
			break;
		case json_type_array:
			object = array_from_json_object(json_object);
			break;
		case json_type_string:
			object = string_from_json_object(json_object);
			break;
	}

	return object;
}

object_t * object_from_json(const char *json)
{
	struct json_object *json_object;
	object_t *object;

	json_object = json_tokener_parse(json);
	object = object_from_json_object(json_object);
	json_object_put(json_object);

	return object;
}

object_t * object_from_json_file(const char *filename)
{
	struct json_object *json_object;
	object_t *object;

	json_object = json_object_from_file(filename);
	object = object_from_json_object(json_object);
	json_object_put(json_object);

	return object;
}

struct json_object * object_to_json_object(object_t *object)
{
	struct json_object *json_object = NULL;

	if (!object_isset(object)) {
		json_object = NULL;
	} else if (object_is_boolean(object)) {
		json_object = json_object_new_boolean(boolean_get(object));
	} else if (object_is_real(object)) {
		json_object = json_object_new_double(real_get(object));
	} else if (object_is_integer(object)) {
		json_object = json_object_new_int(integer_get(object));
	} else if (object_is_hash(object)) {
		json_object = json_object_new_object();
		hash_foreach(object, k, value) {
			struct json_object *jo = object_to_json_object(value);
			json_object_object_add(json_object, k, jo);
		}
	} else if (object_is_array(object)) {
		json_object = json_object_new_array();
		array_foreach(object, value) {
			struct json_object *jo = object_to_json_object(value);
			json_object_array_add(json_object, jo);
		}
	} else if (object_is_string(object)) {
		json_object = json_object_new_string(string_to_c_str(object));
	}

	return json_object;
}

char * object_to_json(object_t *object, int flags)
{
	struct json_object *json_object = NULL;
	const char *json_string;
	char *json;

	if (object) {
		json_object = object_to_json_object(object);
		json_string = json_object_to_json_string_ext(json_object, flags);
		json = object_malloc(sizeof(char) * (strlen(json_string) + 1));
		strcpy(json, json_string);
		json_object_put(json_object);
	}

	return json;
}
