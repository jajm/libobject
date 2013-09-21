#include <stdio.h>
#include <stdlib.h>
#include <libgends/undefined.h>
#include <libgends/iterator.h>
#include <libgends/hash_map.h>
#include "malloc.h"
#include "object.h"
#include "hash.h"
#include "hash_iterator.h"

struct hash_iterator_s {
	const object_t *object;
	gds_iterator_t *iterator;
};

hash_iterator_t * hash_iterator_new(const object_t *object)
{
	hash_iterator_t *hash_iterator;

	if (!object_is_hash(object)) {
		return NULL;
	}

	hash_iterator = object_malloc(sizeof(hash_iterator_t));

	hash_iterator->object = object;
	hash_iterator->iterator = gds_hash_map_iterator_new(object_value(object));

	return hash_iterator;
}

int hash_iterator_reset(hash_iterator_t *hash_iterator)
{
	if (hash_iterator != NULL) {
		return gds_iterator_reset(hash_iterator->iterator);
	}

	return -1;
}

int hash_iterator_step(hash_iterator_t *hash_iterator)
{
	if (hash_iterator != NULL) {
		return gds_iterator_step(hash_iterator->iterator);
	}

	return -1;
}

const char * hash_iterator_get_key(hash_iterator_t *hash_iterator)
{
	if (hash_iterator != NULL) {
		return gds_iterator_getkey(hash_iterator->iterator);
	}

	return UNDEFINED;
}

object_t * hash_iterator_get_value(hash_iterator_t *hash_iterator)
{
	if (hash_iterator != NULL) {
		return gds_iterator_get(hash_iterator->iterator);
	}

	return UNDEFINED;
}

void hash_iterator_free(hash_iterator_t *hash_iterator)
{
	if (hash_iterator != NULL) {
		gds_iterator_free(hash_iterator->iterator);
		free(hash_iterator);
	}
}
