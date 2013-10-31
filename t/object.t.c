#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "type.h"
#include "tap.h"

int main()
{
	object_t *o;
	char *s;
	const char *string_type = "STRING";
	type_t *type;

	plan(9);
	
	type = type_get(string_type);
	type_set_callback(type, "free", free);

	s = calloc(20, sizeof(char));
	strcpy(s, "Hello, object world");

	o = object_new(string_type, s);
	ok(o != NULL, "object is not NULL");
	ok(object_isset(o), "object is set");
	ok(object_isa(o, string_type), "object isa '%s'", string_type);
	str_eq(object_type(o), string_type);
	ok(object_type(o) == string_type, "object_type() returns direct pointer to type string");
	str_eq(object_value(o), s);
	ok(object_value(o) == s, "object_value() returns direct pointer to value");

	object_set(o, "Goodbye");
	str_eq(object_value(o), "Goodbye");
	object_set(o, s);

	object_free(o);
	ok(object_isset(NULL) == 0, "NULL is considered as an unset object");

	types_finalize();

	return 0;
}
