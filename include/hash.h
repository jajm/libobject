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

hash_t *
hash_new(void);

hash_t *
hash_new_from_array(
	unsigned int n,
	void *objects[]
);

#define hash(...) ({ \
	void *__args[] = { __VA_ARGS__ }; \
	hash_new_from_array(sizeof(__args) / sizeof(*__args), __args); \
})

int
hash_set(
	hash_t *hash,
	const char *key,
	object_t *value
);

int
hash_unset(
	hash_t *hash,
	const char *key
);

object_t *
hash_get(
	const hash_t *hash,
	const char *key
);

array_t *
hash_keys(
	const hash_t *hash
);

array_t *
hash_values(
	const hash_t *hash
);

void
hash_free(
	hash_t *hash
);

int
object_is_hash(
	const object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_hash_h_included */

