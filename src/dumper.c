#include <stdio.h>
#include "object.h"
#include "array.h"
#include "hash.h"
#include "integer.h"
#include "real.h"
#include "boolean.h"
#include "string.h"
#include "dumper.h"

void object_dump_into_string(string_t *dump, object_t *object,
	unsigned int indent, _Bool hash_value)
{
	char buffer[32];

	if (!hash_value) {
		for (unsigned int i = 0; i < indent; i++) {
			string_cat(dump, " ");
		}
	}
	if (!object_isset(object)) {
		string_cat(dump, "null()");
	} else if (object_is_array(object)) {
		string_cat(dump, "array(\n");
		array_foreach(object, o) {
			object_dump_into_string(dump, o, indent+2, false);
			string_cat(dump, ",\n");
		}
		for (unsigned int i = 0; i < indent; i++) {
			string_cat(dump, " ");
		}
		string_cat(dump, ")");
	} else if (object_is_hash(object)) {
		string_cat(dump, "hash(\n");
		hash_foreach(object, k, o) {
			for (unsigned int i = 0; i < indent+2; i++) {
				string_cat(dump, " ");
			}
			string_cat(dump, "\"", k, "\"", ", ");
			object_dump_into_string(dump, o, indent+2, true);
			string_cat(dump, ",\n");
		}
		for (unsigned int i = 0; i < indent; i++) {
			string_cat(dump, " ");
		}
		string_cat(dump, ")");
	} else if (object_is_integer(object)) {
		sprintf(buffer, "integer(%d)", integer_get(object));
		string_cat(dump, buffer);
	} else if (object_is_real(object)) {
		sprintf(buffer, "real(%lf)", real_get(object));
		string_cat(dump, buffer);
	} else if (object_is_boolean(object)) {
		if (boolean_get(object)) {
			string_cat(dump, "boolean(true)");
		} else {
			string_cat(dump, "boolean(false)");
		}
	} else if (object_is_string(object)) {
		string_cat(dump, "string(\"", string_to_c_str(object), "\")");
	} else {
		string_cat(dump, "UNKNOWN TYPE (", object_type(object), ")");
	}
}

string_t * object_dump(object_t *object, const char *name)
{
	string_t *dump;

	dump = string("");
	string_cat(dump, name, " = ");
	object_dump_into_string(dump, object, 0, false);
	string_cat(dump, ";");

	return dump;
}
