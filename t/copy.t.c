#include <stdio.h>
#include "object.h"
#include "array.h"
#include "hash.h"
#include "boolean.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "dumper.h"
#include "tap.h"

int main()
{
	object_t *object, *copy;

	plan(10);

	object = hash(
		"string", string("foo"),
		"real", real(4.2),
		"integer", integer(42),
		"boolean", boolean(true),
		"array", array(
			integer(1),
			integer(2),
			integer(3)
		)
	);

	copy = object_copy(object);

	hash_set(object, "string", string("bar"));
	ok(!strcmp("bar", string_to_c_str(hash_get(object, "string"))), "object[\"string\"] is \"bar\"");
	ok(!strcmp("foo", string_to_c_str(hash_get(copy, "string"))), "copy[\"string\"] is \"foo\"");

	hash_set(object, "real", real(3.4));
	ok(real_get(hash_get(object, "real")) == 3.4, "object[\"real\"] == 3.4");
	ok(real_get(hash_get(copy, "real")) == 4.2, "copy[\"real\"] == 4.2");

	hash_set(object, "integer", integer(34));
	ok(integer_get(hash_get(object, "integer")) == 34, "object[\"integer\"] == 34");
	ok(integer_get(hash_get(copy, "integer")) == 42, "copy[\"integer\"] == 42");

	hash_set(object, "boolean", boolean(false));
	ok(boolean_get(hash_get(object, "boolean")) == false, "object[\"boolean\"] is false");
	ok(boolean_get(hash_get(copy, "boolean")) == true, "copy[\"boolean\"] is true");

	array_splice(hash_get(object, "array"), 0, 3, NULL);
	ok(array_size(hash_get(object, "array")) == 0, "object[\"array\"] contains 0 elements");
	ok(array_size(hash_get(copy, "array")) == 3, "copy[\"array\"] contains 3 elements");

	object_free(copy);
	object_free(object);

	return 0;
}
