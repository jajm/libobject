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
#include <libgends/hash_map.h>
#include "log.h"
#include "exception.h"
#include "type.h"
#include "malloc.h"
#include "object.h"
#include "array.h"
#include "hash.h"

#define HASH_SIZE 512

unsigned int hash_hash_callback(const char *key, unsigned int size)
{
	unsigned int hash = 0, i;

	for (i=0; key[i] != '\0'; i++) {
		hash += key[i] * i;
	}
	hash %= size;

	return hash;
}

int hash_cmpkey_callback(const char *key1, const char *key2)
{
	return strcmp(key1, key2);
}

static const char hash_type[] = "HASH";

#define assert_object_is_hash(object) \
	if (!object_is_hash(object)) \
		object_throw_bad_type(object, hash_type)

void hash_free_callback(gds_hash_map_t *gds_hash_map)
{
	gds_hash_map_free(gds_hash_map, free, (gds_free_cb) object_free);
}

static _Bool hash_type_registered = false;

iterator_t * hash_iterator_new(const object_t *object);

void hash_type_register(void)
{
	type_t *type;

	if (!hash_type_registered) {
		type = type_get(hash_type);
		type_set_callback(type, "free", hash_free_callback);
		type_set_callback(type, "iterator", hash_iterator_new);
		hash_type_registered = true;
	}
}

hash_t * hash_new(void)
{
	hash_t *hash;
	gds_hash_map_t *gds_hash_map;

	hash_type_register();

	gds_hash_map = gds_hash_map_new(HASH_SIZE,
		(gds_hash_cb) hash_hash_callback,
		(gds_cmpkey_cb) hash_cmpkey_callback);

	hash = object_new(hash_type, gds_hash_map);
	return hash;
}

hash_t * hash_new_from_array(unsigned int n, void *objects[])
{
	hash_t *hash;
	unsigned int i;

	hash = hash_new();
	for (i=1; i<n; i+=2) {
		const char *key = objects[i-1];
		object_t *value = objects[i];
		hash_set(hash, key, value);
	}

	return hash;
}

int hash_set(hash_t *hash, const char *key, object_t *value)
{
	gds_hash_map_t *gds_hash_map;
	char *k;
	size_t len;

	assert_object_is_hash(hash);

	len = strlen(key);
	k = object_malloc(sizeof(char) * (len+1));
	strncpy(k, key, len+1);

	gds_hash_map = object_value(hash);
	return gds_hash_map_set(gds_hash_map, k, value, free,
		(gds_free_cb) object_free);
}

int hash_unset(hash_t *hash, const char *key)
{
	gds_hash_map_t *gds_hash_map;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	return gds_hash_map_unset(gds_hash_map, key, (gds_free_cb) free,
		(gds_free_cb) object_free);
}

object_t * hash_get(const hash_t *hash, const char *key)
{
	gds_hash_map_t *gds_hash_map;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	return gds_hash_map_get(gds_hash_map, key);
}

typedef struct {
	const object_t *object;
	gds_iterator_t *iterator;
} hash_iterator_data_t;

int hash_iterator_reset(hash_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_reset(data->iterator);
	}

	return -1;
}

int hash_iterator_step(hash_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_step(data->iterator);
	}

	return -1;
}

object_t * hash_iterator_get(hash_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_get(data->iterator);
	}

	return NULL;
}

const char * hash_iterator_getkey(hash_iterator_data_t *data)
{
	if (data != NULL) {
		return gds_iterator_getkey(data->iterator);
	}

	return NULL;
}

void hash_iterator_free(hash_iterator_data_t *data)
{
	if (data != NULL) {
		gds_iterator_free(data->iterator);
		free(data);
	}
}

iterator_t * hash_iterator_new(const object_t *object)
{
	iterator_t *iterator;
	hash_iterator_data_t *data;

	if (!object_is_hash(object)) {
		return NULL;
	}

	data = object_malloc(sizeof(hash_iterator_data_t));

	data->object = object;
	data->iterator = gds_hash_map_iterator_new(object_value(object));

	iterator = iterator_new(data,
		(iterator_reset_cb) hash_iterator_reset,
		(iterator_step_cb) hash_iterator_step,
		(iterator_get_cb) hash_iterator_get,
		(iterator_getkey_cb) hash_iterator_getkey,
		(iterator_free_cb) hash_iterator_free);

	return iterator;
}

array_t * hash_keys(const hash_t *hash)
{
	gds_hash_map_t *gds_hash_map;
	gds_slist_t *gds_keys;
	char *key;
	array_t *keys;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	gds_keys = gds_hash_map_keys(gds_hash_map);
	keys = array();
	gds_slist_foreach(key, gds_keys) {
		array_push(keys, string(key));
	}
	gds_slist_free(gds_keys, NULL, NULL);

	return keys;
}

array_t * hash_values(const hash_t *hash)
{
	gds_hash_map_t *gds_hash_map;
	gds_slist_t *gds_values;
	object_t *value;
	array_t *values;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	gds_values = gds_hash_map_values(gds_hash_map);
	values = array();
	gds_slist_foreach(value, gds_values) {
		array_push(values, object_get_ref(value));
	}
	gds_slist_free(gds_values, NULL, NULL);

	return values;
}

void hash_free(hash_t *hash)
{
	assert_object_is_hash(hash);

	object_free(hash);
}

int object_is_hash(const object_t *object)
{
	if (object_isa(object, hash_type))
		return 1;

	return 0;
}
