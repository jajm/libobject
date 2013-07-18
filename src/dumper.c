#include <stdio.h>
#include "object.h"
#include "array.h"
#include "array_iterator.h"
#include "hash.h"
#include "integer.h"
#include "real.h"
#include "boolean.h"
#include "string.h"
#include "dumper.h"

void object_dump_object(object_t *object, unsigned int indent, _Bool hash_value)
{
	if (!hash_value) {
		for (unsigned int i = 0; i < indent; i++) {
			printf(" ");
		}
	}
	if (object_is_array(object)) {
		printf("array(\n");
		array_foreach(object, o) {
			object_dump_object(o, indent+2, false);
			printf(",\n");
		}
		for (unsigned int i = 0; i < indent; i++) {
			printf(" ");
		}
		printf(")");
	} else if (object_is_hash(object)) {
		printf("hash(\n");
		array_t *keys = hash_keys(object);
		array_foreach(keys, key) {
			const char *k = string_to_c_str(key);
			object_t *o = hash_get(object, k);
			object_dump_object(key, indent+2, false);
			printf(", ");
			object_dump_object(o, indent+2, true);
			printf(",\n");
		}
		array_free(keys, string_free, NULL);
		for (unsigned int i = 0; i < indent; i++) {
			printf(" ");
		}
		printf(")");
	} else if (object_is_integer(object)) {
		printf("%d", integer_get(object));
	} else if (object_is_real(object)) {
		printf("%lf", real_get(object));
	} else if (object_is_boolean(object)) {
		printf("%s", boolean_get(object) ? "true" : "false");
	} else if (object_is_string(object)) {
		printf("\"%s\"", string_to_c_str(object));
	} else {
		printf("UNKNOWN TYPE (%s)", object_type(object));
	}
}

void object_dump(object_t *object, const char *name)
{
	printf("%s = ", name);
	object_dump_object(object, 0, false);
	printf(";\n");
}
