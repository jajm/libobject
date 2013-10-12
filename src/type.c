#include <stdlib.h>
#include <string.h>
#include <libgends/hash_map_keyin.h>
#include <libgends/hash_map.h>
#include "log.h"
#include "exception.h"
#include "malloc.h"
#include "type.h"

struct type_s {
	const char *name;
	gds_hash_map_t *callbacks;
};

#define CALLBACKS_SIZE 16

unsigned int type_callbacks_hash_cb(const char *key, unsigned int size)
{
	unsigned int hash = 0, i;

	for (i=0; key[i] != '\0'; i++) {
		hash += key[i] * i;
	}
	hash %= size;

	return hash;
}

#define TYPE_MAP_SIZE 32

gds_hash_map_keyin_t *type_map = NULL;

unsigned int type_map_hash_cb(const char *key, unsigned int size)
{
	unsigned int hash = 0, i;

	for (i=0; key[i] != '\0'; i++) {
		hash += key[i] * i;
	}
	hash %= size;

	return hash;
}

const char * type_map_getkey_cb(type_t *type)
{
	return type->name;
}

int type_map_cmpkey_cb(const char *key1, const char *key2)
{
	return strcmp(key1, key2);
}

void types_initialize()
{
	if (type_map != NULL) {
		types_finalize();
		gds_hash_map_keyin_free(type_map, free);
	}
	type_map = gds_hash_map_keyin_new(TYPE_MAP_SIZE,
		(gds_hash_cb) type_map_hash_cb,
		(gds_getkey_cb) type_map_getkey_cb,
		(gds_cmpkey_cb) strcmp);
}

int types_initialized()
{
	if (type_map != NULL)
		return 1;

	return 0;
}

void type_map_assert_initialized(void)
{
	if (!types_initialized()) {
		types_initialize();
	}
}

type_t * type_new(const char *name)
{
	type_t *type;

	type = object_malloc(sizeof(type_t));

	type->name = name;
	type->callbacks = gds_hash_map_new(CALLBACKS_SIZE,
		(gds_hash_cb) type_callbacks_hash_cb,
		(gds_cmpkey_cb) strcmp);

	return type;
}


type_t * type_get(const char *name)
{
	type_t *type;

	type_map_assert_initialized();

	type = gds_hash_map_keyin_get(type_map, name);
	if (type == NULL) {
		type = type_new(name);
		gds_hash_map_keyin_set(type_map, type, NULL);
	}

	return type;
}

const char * type_name(type_t *type)
{
	if (type != NULL) {
		return type->name;
	}
	return NULL;
}

void type_set_callback(type_t *type, const char *name, void *callback)
{
	char *_name;
	size_t len;

	if (type != NULL && name != NULL && callback != NULL) {
		if (gds_hash_map_get(type->callbacks, name) == NULL) {
			len = strlen(name);
			_name = object_malloc(sizeof(char) * (len+1));
			strncpy(_name, name, len+1);
			gds_hash_map_set(type->callbacks, _name, callback, NULL,
				NULL);
		}
	}
}

void * type_get_callback(type_t *type, const char *name)
{
	void *callback = NULL;

	if (type != NULL && name != NULL) {
		callback = gds_hash_map_get(type->callbacks, name);
	}

	return callback;
}

void type_free(type_t *type)
{
	if (type != NULL) {
		gds_hash_map_free(type->callbacks, free, NULL);
		free(type);
	}
}

void types_finalize()
{
	gds_hash_map_keyin_free(type_map, (gds_free_cb)type_free);
	type_map = NULL;
}
