#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgends/hash_map.h>
#include "log.h"
#include "exception.h"
#include "object.h"
#include "array.h"
#include "hash.h"

#define HASH_SIZE 512

unsigned int hash_hash_callback(string_t *string, unsigned int size)
{
	const char *s;
	unsigned int hash = 0, i;

	s = string_to_c_str(string);
	for (i=0; s[i] != '\0'; i++) {
		hash += s[i] * i;
	}
	hash %= size;

	return hash;
}

int hash_cmpkey_callback(string_t *string1, string_t *string2)
{
	const char *s1, *s2;

	s1 = string_to_c_str(string1);
	s2 = string_to_c_str(string2);

	return strcmp(s1, s2);
}

static const char hash_type[] = "HASH";

#define assert_object_is_hash(object) \
	if (!object_is_hash(object)) \
		object_throw_bad_type(object, hash_type)

hash_t * hash_new(void)
{
	hash_t *hash;
	gds_hash_map_t *gds_hash_map;

	gds_hash_map = gds_hash_map_new(HASH_SIZE,
		(gds_hash_cb) hash_hash_callback,
		(gds_cmpkey_cb) hash_cmpkey_callback);

	hash = object_new(hash_type, gds_hash_map);
	return hash;
}

hash_t * hash_new_from_array(unsigned int n, object_t *objects[])
{
	hash_t *hash;
	unsigned int i;

	hash = hash_new();
	for (i=1; i<n; i+=2) {
		string_t *key = objects[i-1];
		object_t *value = objects[i];
		hash_set(hash, key, value);
	}

	return hash;
}

int hash_set(hash_t *hash, string_t *key, object_t *value)
{
	gds_hash_map_t *gds_hash_map;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	return gds_hash_map_set(gds_hash_map, key, value, NULL);
}

int hash_unset(hash_t *hash, string_t *key, void *callback)
{
	gds_hash_map_t *gds_hash_map;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	return gds_hash_map_unset(gds_hash_map, key, (gds_free_cb) string_free,
		(gds_free_cb) callback);
}

object_t * hash_get(hash_t *hash, string_t *key)
{
	gds_hash_map_t *gds_hash_map;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	return gds_hash_map_get(gds_hash_map, key);
}


array_t * hash_keys(hash_t *hash)
{
	gds_hash_map_t *gds_hash_map;
	gds_slist_t *gds_keys;
	string_t *key;
	array_t *keys;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	gds_keys = gds_hash_map_keys(gds_hash_map);
	keys = array();
	gds_slist_foreach(key, gds_keys) {
		array_push(keys, key);
	}
	gds_slist_free(gds_keys, NULL, NULL);

	return keys;
}

array_t * hash_values(hash_t *hash)
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
		array_push(values, value);
	}
	gds_slist_free(gds_values, NULL, NULL);

	return values;
}

void hash_free(hash_t *hash, void *callback)
{
	gds_hash_map_t *gds_hash_map;

	assert_object_is_hash(hash);

	gds_hash_map = object_value(hash);
	gds_hash_map_free(gds_hash_map, (gds_free_cb) string_free,
		(gds_free_cb) callback);
	object_free(hash, NULL, NULL);
}

int object_is_hash(object_t *object)
{
	if (object_isa(object, hash_type))
		return 1;

	return 0;
}
