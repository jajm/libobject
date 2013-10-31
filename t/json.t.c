#include <stdio.h>
#include <stdlib.h>
#include "dumper.h"
#include "json.h"
#include "array.h"
#include "hash.h"
#include "string.h"
#include "real.h"
#include "integer.h"
#include "boolean.h"
#include "type.h"
#include "tap.h"

int main()
{
	object_t *object, *o;
	const char json[] = "['a', 'b', 'c', {'d': 'e', 'f': 'g'}, null]";
	const char json2[] = "{'real': 2.3, 'integer': 2, 'boolean': true, 'string': 'foobar'}";

	plan(31);

	diag("object = object_from_json(\"%s\");", json);
	object = object_from_json(json);
	ok(object_is_array(object), "object is array");
	o = array_get(object, 0);
	ok(object_is_string(o), "object[0] is string");
	ok(strcmp(string_to_c_str(o), "a") == 0, "object[0] == \"a\"");
	o = array_get(object, 1);
	ok(object_is_string(o), "object[1] is string");
	ok(strcmp(string_to_c_str(o), "b") == 0, "object[1] == \"b\"");
	o = array_get(object, 2);
	ok(object_is_string(o), "object[2] is string");
	ok(strcmp(string_to_c_str(o), "c") == 0, "object[2] == \"c\"");
	o = array_get(object, 3);
	ok(object_is_hash(o), "object[3] is hash");
	o = array_get(object, 4);
	ok(!object_isset(o), "object[4] is null");
	object_free(object);

	diag("object = object_from_json(\"%s\");", json2);
	object = object_from_json(json2);
	ok(object_is_hash(object), "object is hash");
	o = hash_get(object, "real");
	ok(object_is_real(o), "object[\"real\"] is real");
	ok(real_get(o) == 2.3, "object[\"real\"] == 2.3");
	o = hash_get(object, "integer");
	ok(object_is_integer(o), "object[\"integer\"] is integer");
	ok(integer_get(o) == 2, "object[\"integer\"] == 2");
	o = hash_get(object, "boolean");
	ok(object_is_boolean(o), "object[\"boolean\"] is boolean");
	ok(boolean_get(o), "object[\"boolean\"] is true");
	o = hash_get(object, "string");
	ok(object_is_string(o), "object[\"string\"] is string");
	ok(strcmp(string_to_c_str(o), "foobar") == 0, "object[\"string\"] == \"foobar\"");
	object_free(object);

	diag("object = object_from_json_file(\"t/test_json.json\");");
	object = object_from_json_file("t/test_json.json");
	ok(object_is_hash(object), "object is hash");
	o = hash_get(object, "one");
	ok(object_is_integer(o), "object[\"one\"] is integer");
	ok(integer_get(o) == 1, "object[\"one\"] == 1");
	o = hash_get(object, "two");
	ok(object_is_array(o), "object[\"two\"] is array");
	ok(array_size(o) == 2, "object[\"two\"] is of size 2");
	o = hash_get(object, "three");
	ok(object_is_real(o), "object[\"three\"] is real");
	ok(real_get(o) == 3.33, "object[\"three\"] == 3.33");
	o = hash_get(object, "four");
	ok(object_is_string(o), "object[\"four\"] is string");
	ok(strcmp(string_to_c_str(o), "four") == 0, "object[\"four\"] == \"four\"");

	char *json_string = object_to_json(object, OBJECT_TO_JSON_PLAIN);
	diag("object_to_json(object, OBJECT_TO_JSON_PLAIN) == %s", json_string);
	ok(strstr(json_string, "\"one\":1") != NULL, "json_string contains \"one\":1");
	ok(strstr(json_string, "\"two\":[2,2]") != NULL, "json_string contains \"two\":[2,2]");
	ok(strstr(json_string, "\"three\":3.330000") != NULL, "json_string contains \"three\":3.330000");
	ok(strstr(json_string, "\"four\":\"four\"") != NULL, "json_string contains \"four\":\"four\"");
	free(json_string);

	object_free(object);

	types_finalize();
}
