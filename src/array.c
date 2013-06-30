#include <stdio.h>
#include <libgends/dlist.h>
#include <libgends/undefined.h>
#include "array.h"

static const char array_type[] = "ARRAY";

object_t * array_new(unsigned int size, void *values[])
{
	gds_dlist_t *list = gds_dlist_new_from_array(size, values);
	if (list == NULL) {
		fprintf(stderr, "List creation failed\n");
		return NULL;
	}

	return object_new(array_type, list);
}

void array_push(object_t *object, void *value)
{
	if (!object_is_array(object)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	gds_dlist_push(object_value(object), value);
}

void array_unshift(object_t *object, void *value)
{
	if (!object_is_array(object)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	gds_dlist_unshift(object_value(object), value);
}

void * array_pop(object_t *object)
{
	if (!object_is_array(object)) {
		fprintf(stderr, "object is not an array\n");
		return UNDEFINED;
	}
	return gds_dlist_pop(object_value(object));
}

void * array_shift(object_t *object)
{
	if (!object_is_array(object)) {
		fprintf(stderr, "object is not an array\n");
		return UNDEFINED;
	}
	return gds_dlist_shift(object_value(object));
}

unsigned int array_size(object_t *object)
{
	if (!object_is_array(object)) {
		fprintf(stderr, "object is not an array\n");
		return 0;
	}
	return gds_dlist_size(object_value(object));
}

void array_free(object_t *object, void *callback, void *callback_data)
{
	if (!object_is_array(object)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	gds_dlist_free(object_value(object), callback, callback_data);
	object_free(object, NULL, NULL);
}

int object_is_array(object_t *object)
{
	if (object_isa(object, array_type))
		return 1;
	
	return 0;
}
