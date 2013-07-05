#include <stdio.h>
#include <libgends/dlist.h>
#include "object.h"
#include "array.h"

static const char array_type[] = "ARRAY";

array_t * array_new(unsigned int size, object_t *objects[])
{
	gds_dlist_t *list = gds_dlist_new_from_array(size, (void **)objects);
	if (list == NULL) {
		fprintf(stderr, "List creation failed\n");
		return NULL;
	}

	return object_new(array_type, list);
}

void array_push(array_t *array, object_t *object)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	gds_dlist_push(object_value(array), object);
}

void array_unshift(array_t *array, object_t *object)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	gds_dlist_unshift(object_value(array), object);
}

object_t * array_pop(array_t *array)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return NULL;
	}
	return gds_dlist_pop(object_value(array));
}

object_t * array_shift(array_t *array)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return NULL;
	}
	return gds_dlist_shift(object_value(array));
}

object_t * array_get(array_t *array, unsigned int offset)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return NULL;
	}
	return gds_dlist_get(object_value(array), offset);
}

void array_splice(array_t *array, unsigned int offset, unsigned int length,
	void *callback, void *callback_data, array_t *replacement)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	if (replacement != NULL && !object_is_array(replacement)) {
		fprintf(stderr, "replacement is not an array\n");
		return;
	}
	gds_dlist_splice(object_value(array), offset, length, callback,
		callback_data, object_value(replacement));
}

array_t * array_slice(array_t *array, unsigned int offset, unsigned int length,
	void *callback, void *callback_data)
{
	gds_dlist_t *slice;

	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return NULL;
	}

	slice = gds_dlist_slice(object_value(array), offset, length, callback,
		callback_data);
	return object_new(array_type, slice);
}

void array_map(array_t *array, void *callback, void *callback_data)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	gds_dlist_map(object_value(array), callback, callback_data);
}

array_t * array_filter(array_t *array, void *callback, void *callback_data)
{
	gds_dlist_t *filtered;
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return NULL;
	}
	filtered = gds_dlist_filter(object_value(array), callback,
		callback_data);
	return object_new(array_type, filtered);
}

object_t * array_reduce(array_t *array, void *callback, void *callback_data)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return NULL;
	}
	return gds_dlist_reduce(object_value(array), callback, callback_data);
}

unsigned int array_size(array_t *array)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return 0;
	}
	return gds_dlist_size(object_value(array));
}

void array_free(array_t *array, void *callback, void *callback_data)
{
	if (!object_is_array(array)) {
		fprintf(stderr, "object is not an array\n");
		return;
	}
	gds_dlist_free(object_value(array), callback, callback_data);
	object_free(array, NULL, NULL);
}

int object_is_array(object_t *object)
{
	if (object_isa(object, array_type))
		return 1;
	
	return 0;
}
