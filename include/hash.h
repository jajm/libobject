#ifndef object_hash_h_included
#define object_hash_h_included

#include "object.h"
#include "string.h"
#include "array.h"
#include "iterator.h"

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

iterator_t *
hash_iterator_new(
	const object_t *object
);

#define hash_foreach(hash, key, value) \
	for (iterator_t *__it = hash_iterator_new(hash) \
		; __it != NULL \
		; iterator_free(__it), __it = NULL) \
	while (!iterator_step(__it)) \
	for (const char *key = iterator_getkey(__it); key; key = NULL) \
	for (object_t *value = iterator_get(__it), *__b = 0; \
		__b == 0; __b = (object_t *)1)

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

