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

#endif /* ! object_hash_h_included */

