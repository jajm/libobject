#ifndef object_hash_h_included
#define object_hash_h_included

#include "object.h"
#include "string.h"
#include "array.h"

typedef object_t hash_t;

hash_t *
hash_new(void);

hash_t *
hash_new_from_array(
	unsigned int n,
	object_t *objects[]
);

#define hash(...) ({ \
	object_t *__args[] = { __VA_ARGS__ }; \
	hash_new_from_array(sizeof(__args) / sizeof(*__args), __args); \
})

int
hash_set(
	hash_t *hash,
	string_t *key,
	object_t *value
);

int
hash_unset(
	hash_t *hash,
	string_t *key,
	void *callback
);

object_t *
hash_get(
	hash_t *hash,
	string_t *key
);

array_t *
hash_keys(
	hash_t *hash
);

array_t *
hash_values(
	hash_t *hash
);

void
hash_free(
	hash_t *hash,
	void *callback
);

int
object_is_hash(
	object_t *object
);

#endif /* ! object_hash_h_included */

