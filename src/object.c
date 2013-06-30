#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

struct object_s {
	char *type;
	void *value;
};

object_t * object_new(const char *type, void *value)
{
	object_t *object;

	if (type == NULL) {
		fprintf(stderr, "type cannot be NULL\n");
		return NULL;
	}

	object = malloc(sizeof(object_t));
	if (object == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}

	object->type = NULL;
	if(0 > object_set(object, type, value)) {
		free(object);
		return NULL;
	}

	return object;
}

const char * object_type(object_t *object)
{
	const char *type = NULL;

	if (object != NULL) {
		type = object->type;
	}

	return type;
}

void * object_value(object_t *object)
{
	void *value = NULL;

	if (object != NULL) {
		value = object->value;
	}

	return value;
}

int object_set(object_t *object, const char *type, void *value)
{
	size_t length;

	if (object != NULL) {
		length = strlen(type);
		free(object->type);
		object->type = malloc(sizeof(char) * (length+1));
		if (object->type == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			return -1;
		}

		strncpy(object->type, type, length+1);
		object->value = value;
	}

	return 0;
}

void object_unset(object_t *object, void *callback, void *callback_data)
{
	void (*cb)(void *, void *) = callback;

	if (object != NULL) {
		if (cb != NULL) {
			cb(object->value, callback_data);
		}
		object_set(object, "", NULL);
	}
}

int object_isset(object_t *object)
{
	if (object != NULL && object->type != NULL && object->type[0] != '\0')
		return 1;
	
	return 0;
}

int object_isa(object_t *object, const char *type)
{
	if (object_isset(object) && type != NULL && !strcmp(object->type, type))
		return 1;
	
	return 0;
}

void object_free(object_t *object, void *callback, void *callback_data)
{
	void (*cb)(void *, void *) = callback;

	if (object != NULL) {
		if (cb != NULL) {
			cb(object->value, callback_data);
		}
		free(object->type);
		free(object);
	}
}
