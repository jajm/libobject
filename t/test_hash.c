#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "array_iterator.h"
#include "hash.h"

int main()
{
	hash_t *hash;

	hash = hash_new();

	hash_set(hash, string("clé"), string("valeur"));
	string_t *key = string("clé");
	object_t *value = hash_get(hash, key);
	string_free(key);
	printf("%s\n", string_to_c_str(value));

	hash_free(hash, string_free);

	hash = hash(
		string("clé 1"), string("valeur 1"),
		string("clé 2"), string("valeur 2"),
		string("clé 3"), string("valeur 3")
	);

	array_t *keys = hash_keys(hash);
	printf("Keys:\n");
	array_foreach(keys, key) {
		printf("%s\n", string_to_c_str(key));
	}
	array_free(keys, NULL, NULL);

	array_t *values = hash_values(hash);
	printf("Values:\n");
	array_foreach(values, value) {
		printf("%s\n", string_to_c_str(value));
	}
	array_free(values, NULL, NULL);

	hash_free(hash, string_free);

	return 0;
}
