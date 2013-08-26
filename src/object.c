#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libexception/exception.h>
#include "log.h"
#include "exception.h"
#include "type.h"
#include "malloc.h"
#include "object.h"

struct object_s {
	type_t *type;
	void *value;
	_Bool is_ref;
};

object_t * object_new(const char *type, void *value)
{
	object_t *object = NULL;

	if (type == NULL) {
		log_error("type cannot be NULL");
		return NULL;
	}

	object = object_malloc(sizeof(object_t));

	object->type = type_get(type);
	object->value = value;
	object->is_ref = false;

	return object;
}

object_t * object_new_ref(const char *type, void *value)
{
	object_t *ref;

	ref = object_malloc(sizeof(object_t));

	ref->type = type_get(type);
	ref->value = value;
	ref->is_ref = true;

	return ref;
}

object_t * object_get_ref(object_t *object)
{
	object_t *ref;

	ref = object_malloc(sizeof(object_t));

	ref->type = object->type;
	ref->value = object->value;
	ref->is_ref = true;

	return ref;
}

const char * object_type(const object_t *object)
{
	const char *type = NULL;

	if (object_isset(object)) {
		type = type_name(object->type);
	}

	return type;
}

void * object_value(const object_t *object)
{
	void *value = NULL;

	if (object != NULL) {
		value = object->value;
	}

	return value;
}

int object_isset(const object_t *object)
{
	if (object != NULL && object->type != NULL)
		return 1;

	return 0;
}

int object_isa(const object_t *object, const char *type)
{
	const char *typename;

	if (object_isset(object)) {
		typename = type_name(object->type);
		if (type == typename || !strcmp(typename, type))
			return 1;
	}

	return 0;
}

void object_free_value(object_t *object)
{
	void (*free_callback)(void *);

	free_callback = type_get_callback(object->type, "free");
	if (free_callback != NULL) {
		free_callback(object->value);
	}
}

void object_free(object_t *object)
{
	if (object_isset(object) && !object->is_ref) {
		object_free_value(object);
	}
	free(object);
}
