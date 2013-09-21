#ifndef object_hash_iterator_h_included
#define object_hash_iterator_h_included

typedef struct hash_iterator_s hash_iterator_t;

hash_iterator_t *
hash_iterator_new(
	const object_t *object
);

int
hash_iterator_reset(
	hash_iterator_t *hash_iterator
);

int
hash_iterator_step(
	hash_iterator_t *hash_iterator
);

const char *
hash_iterator_get_key(
	hash_iterator_t *hash_iterator
);

object_t *
hash_iterator_get_value(
	hash_iterator_t *hash_iterator
);

void
hash_iterator_free(
	hash_iterator_t *hash_iterator
);

#define hash_foreach(hash, key, value) \
	for (hash_iterator_t *__it = hash_iterator_new(hash) \
		; __it != NULL \
		; hash_iterator_free(__it), __it = NULL) \
	while (!hash_iterator_step(__it)) \
	for (const char *key = hash_iterator_get_key(__it); key; key = NULL) \
	for (object_t *value = hash_iterator_get_value(__it), *__b = 0; \
		__b == 0; __b = (object_t *)1)

#endif /* ! object_hash_iterator_h_included */

