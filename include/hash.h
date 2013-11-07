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

#ifndef object_hash_h_included
#define object_hash_h_included

#include "object.h"
#include "string.h"
#include "array.h"
#include "iterator.h"

typedef object_t hash_t;

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new hash.
 *
 * Returns
 *   Pointer to hash.
 */
hash_t *
hash_new(void);

/* Create a new hash from an array of objects.
 *
 * Parameters
 *   n       : Size of array.
 *   objects : Array of objects.
 *
 * Returns
 *   Pointer to hash.
 */
hash_t *
hash_new_from_array(
	unsigned int n,
	void *objects[]
);

#define hash(...) ({ \
	void *__args[] = { __VA_ARGS__ }; \
	hash_new_from_array(sizeof(__args) / sizeof(*__args), __args); \
})

/* Set/Add a value in the hash.
 *
 * If key is already present in the hash, associated object is freed before
 * changing the value.
 *
 * Parameters
 *   hash  : Pointer to hash.
 *   key   : Key associated to value.
 *   value : Value to insert into hash.
 *
 * Returns
 *   0 if key was just added.
 *   1 if key was already in the hash.
 */
int
hash_set(
	hash_t *hash,
	const char *key,
	object_t *value
);

/* Unset a value from the hash.
 *
 * Parameters
 *   hash : Pointer to hash.
 *   key  : Key to unset.
 *
 * Returns
 *   0 if key was correctly unset.
 *   1 if key was not in the hash.
 */
int
hash_unset(
	hash_t *hash,
	const char *key
);

/* Retrieve a value from the hash.
 *
 * Parameters
 *   hash : Pointer to hash.
 *   key  : Key of value to retrieve.
 *
 * Returns
 *   Pointer to value.
 */
object_t *
hash_get(
	const hash_t *hash,
	const char *key
);

/* Return list of keys present in hash.
 *
 * Parameters
 *   hash : Pointer to hash.
 *
 * Returns
 *   an array containing string_t objects representing the keys in the hash.
 */
array_t *
hash_keys(
	const hash_t *hash
);

/* Return list of values present in hash.
 *
 * Parameters
 *   hash : Pointer to hash.
 *
 * Returns
 *   an array containing objects representing the values in the hash.
 */
array_t *
hash_values(
	const hash_t *hash
);

/* Tell if object is a hash.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   0 if object is not a hash.
 *   1 if object is a hash.
 */
int
object_is_hash(
	const object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_hash_h_included */

