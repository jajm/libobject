#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "array_iterator.h"
#include "hash.h"
#include "type.h"
#include "tap.h"

int main()
{
	hash_t *hash;

	plan(7);

	hash = hash_new();
	ok(object_is_hash(hash), "object is hash");

	hash_set(hash, "clé", string("valeur"));
	object_t *value = hash_get(hash, "clé");
	ok(object_is_string(value), "hash[\"clé\"] is string");
	str_eq(string_to_c_str(value), "valeur");

	hash_free(hash);

	hash = hash(
		"clé 1", string("valeur 1"),
		"clé 2", string("valeur 2"),
		"clé 3", string("valeur 3")
	);

	array_t *keys = hash_keys(hash);
	ok(object_is_array(keys), "hash_keys() returns array");
	ok(array_size(keys) == 3, "hash has 3 keys");
	array_free(keys);

	array_t *values = hash_values(hash);
	ok(object_is_array(values), "hash_values() returns array");
	ok(array_size(values) == 3, "hash has 3 values");
	array_free(values);

	hash_free(hash);

	types_finalize();

	return 0;
}
