#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "json.h"
#include "object.h"
#include "hash.h"
#include "array.h"
#include "integer.h"
#include "real.h"
#include "boolean.h"

object_t * json_object_to_object(struct json_object *json_object);

hash_t * json_object_to_hash(struct json_object *json_object)
{
	struct json_object_iterator it, it_end;
	hash_t *hash;

	it = json_object_iter_begin(json_object);
	it_end = json_object_iter_end(json_object);
	hash = hash_new();
	printf("HASH\n");

	while (!json_object_iter_equal(&it, &it_end)) {
		const char *name = json_object_iter_peek_name(&it);
		printf("%s => \n", name);
		struct json_object *value = json_object_iter_peek_value(&it);
		hash_set(hash, name, json_object_to_object(value));
		json_object_iter_next(&it);
	}

	return hash;
}

array_t * json_object_to_array(struct json_object *json_object)
{
	array_t *array;
	struct array_list *array_list;
	int length;
	int idx;

	array = array();
	printf("ARRAY\n");
	array_list = json_object_get_array(json_object);
	length = array_list_length(array_list);
	idx = 0;
	while (idx < length) {
		struct json_object *value = array_list_get_idx(array_list, idx);
		array_push(array, json_object_to_object(value));
		idx++;
	}

	return array();
}

string_t * json_object_to_string(struct json_object *json_object)
{
	string_t *string;
	const char *value;

	value = json_object_get_string(json_object);
	printf("STRING: %s\n", value);
	string = string_new(value);

	return string;
}

object_t * json_object_to_object(struct json_object *json_object)
{
	object_t *object;
	enum json_type type;

	type = json_object_get_type(json_object);
	switch (type) {
		case json_type_null:
			object = object_new("", NULL);
			break;
		case json_type_boolean:
			object = boolean_new(json_object_get_boolean(json_object));
			break;
		case json_type_double:
			object = real_new(json_object_get_double(json_object));
			break;
		case json_type_int:
			object = integer_new(json_object_get_int(json_object));
			break;
		case json_type_object:
			object = json_object_to_hash(json_object);
			break;
		case json_type_array:
			object = json_object_to_array(json_object);
			break;
		case json_type_string:
			object = json_object_to_string(json_object);
			break;
	}

	return object;
}

object_t * object_from_json(const char *json)
{
	struct json_object *json_object;
	object_t *object;

	json_object = json_tokener_parse(json);
	object = json_object_to_object(json_object);

	return object;
}

object_t * object_from_json_file(const char *filename)
{
	struct json_object *json_object;
	object_t *object;

	json_object = json_object_from_file(filename);
	object = json_object_to_object(json_object);

	return object;
}

char * object_to_json(object_t *object)
{
	struct json_object *json_object = NULL;
	const char *json_string;
	char *json;

	// TODO Create json_object
	if (object) {}
	json_string = json_object_to_json_string(json_object);
	json = malloc(sizeof(char) * (strlen(json_string) + 1));
	strcpy(json, json_string);

	return json;
}
