/*
 * Copyright 2013 Julian Maurice
 *
 * This file is part of libobject
 *
 * libobject is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libobject is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libobject.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "object.h"
#include "array.h"
#include "hash.h"
#include "integer.h"
#include "real.h"
#include "boolean.h"
#include "string.h"
#include "foreach.h"
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
		foreach(object, o) {
			object_dump_into_string(dump, o, indent+2, false);
			string_cat(dump, ",\n");
		}
		for (unsigned int i = 0; i < indent; i++) {
			string_cat(dump, " ");
		}
		string_cat(dump, ")");
	} else if (object_is_hash(object)) {
		string_cat(dump, "hash(\n");
		foreachk(object, k, o) {
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
