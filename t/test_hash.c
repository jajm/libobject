#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "hash_iterator.h"
#include "hash.h"
#include "type.h"
#include "tap.h"

int main()
{
	hash_t *hash;

	plan(10);

	hash = hash_new();
	ok(object_is_hash(hash), "object is hash");

	hash_set(hash, "key", string("value"));
	object_t *value = hash_get(hash, "key");
	ok(object_is_string(value), "hash[\"key\"] is string");
	str_eq(string_to_c_str(value), "value");

	hash_free(hash);

	hash = hash(
		"key 1", string("value 1"),
		"key 2", string("value 2"),
		"key 3", string("value 3")
	);

	hash_foreach(hash, key, val) {
		if (!strcmp(key, "key 1")) str_eq(string_to_c_str(val), "value 1");
		if (!strcmp(key, "key 2")) str_eq(string_to_c_str(val), "value 2");
		if (!strcmp(key, "key 3")) str_eq(string_to_c_str(val), "value 3");
	}

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
