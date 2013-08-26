#include <stdbool.h>
#include <stdio.h>
#include <libgends/dlist.h>
#include "log.h"
#include "exception.h"
#include "type.h"
#include "object.h"
#include "array.h"

static const char array_type[] = "ARRAY";

#define assert_object_is_array(object) \
	if (!object_is_array(object)) \
		object_throw_bad_type(object, array_type);

void array_free_callback(gds_dlist_t *list)
{
	gds_dlist_free(list, object_free, NULL);
}

static _Bool array_type_registered = false;

void array_type_register(void)
{
	type_t *type;

	if (!array_type_registered) {
		type = type_get(array_type);
		type_set_callback(type, "free", array_free_callback);
		array_type_registered = true;
	}
}

array_t * array_new(unsigned int size, object_t *objects[])
{
	gds_dlist_t *list;

	array_type_register();

	list = gds_dlist_new_from_array(size, (void **)objects);
	if (list == NULL) {
		log_error("List creation failed");
		return NULL;
	}

	return object_new(array_type, list);
}

void array_push(array_t *array, object_t *object)
{
	assert_object_is_array(array);

	gds_dlist_push(object_value(array), object);
}

void array_unshift(array_t *array, object_t *object)
{
	assert_object_is_array(array);

	gds_dlist_unshift(object_value(array), object);
}

object_t * array_pop(array_t *array)
{
	assert_object_is_array(array);

	return gds_dlist_pop(object_value(array));
}

object_t * array_shift(array_t *array)
{
	assert_object_is_array(array);

	return gds_dlist_shift(object_value(array));
}

object_t * array_get(array_t *array, unsigned int offset)
{
	assert_object_is_array(array);

	return gds_dlist_get(object_value(array), offset);
}

void array_splice(array_t *array, unsigned int offset, unsigned int length,
	void *callback, void *callback_data, array_t *replacement)
{
	assert_object_is_array(array);

	if (replacement != NULL) {
		assert_object_is_array(replacement);
	}

	gds_dlist_splice(object_value(array), offset, length, callback,
		callback_data, object_value(replacement));
}

array_t * array_slice(array_t *array, unsigned int offset, unsigned int length,
	void *callback, void *callback_data)
{
	gds_dlist_t *slice;

	assert_object_is_array(array);

	slice = gds_dlist_slice(object_value(array), offset, length, callback,
		callback_data);

	return object_new(array_type, slice);
}

void array_map(array_t *array, void *callback, void *callback_data)
{
	assert_object_is_array(array);
	gds_dlist_map(object_value(array), callback, callback_data);
}

array_t * array_filter(array_t *array, void *callback, void *callback_data)
{
	gds_dlist_t *filtered;

	assert_object_is_array(array);

	filtered = gds_dlist_filter(object_value(array), callback,
		callback_data);
	return object_new(array_type, filtered);
}

object_t * array_reduce(array_t *array, void *callback, void *callback_data)
{
	assert_object_is_array(array);

	return gds_dlist_reduce(object_value(array), callback, callback_data);
}

unsigned int array_size(array_t *array)
{
	assert_object_is_array(array);

	return gds_dlist_size(object_value(array));
}

void array_free(array_t *array)
{
	assert_object_is_array(array);

	object_free(array);
}

int object_is_array(object_t *object)
{
	if (object_isa(object, array_type))
		return 1;
	
	return 0;
}
