#include <stdio.h>
#include <stdlib.h>
#include <libgends/undefined.h>
#include <libgends/iterator.h>
#include <libgends/dlist.h>
#include "malloc.h"
#include "object.h"
#include "array.h"
#include "array_iterator.h"

struct array_iterator_s {
	object_t *object;
	gds_iterator_t *iterator;
};

array_iterator_t * array_iterator_new(object_t *object)
{
	array_iterator_t *array_iterator;

	if (!object_is_array(object)) {
		return NULL;
	}

	array_iterator = object_malloc(sizeof(array_iterator_t));

	array_iterator->object = object;
	array_iterator->iterator = gds_dlist_iterator_new(object_value(object));

	return array_iterator;
}

int array_iterator_reset(array_iterator_t *array_iterator)
{
	if (array_iterator != NULL) {
		return gds_iterator_reset(array_iterator->iterator);
	}

	return -1;
}

int array_iterator_step(array_iterator_t *array_iterator)
{
	if (array_iterator != NULL) {
		return gds_iterator_step(array_iterator->iterator);
	}

	return -1;
}

object_t * array_iterator_get(array_iterator_t *array_iterator)
{
	if (array_iterator != NULL) {
		return gds_iterator_get(array_iterator->iterator);
	}

	return UNDEFINED;
}

void array_iterator_free(array_iterator_t *array_iterator)
{
	if (array_iterator != NULL) {
		gds_iterator_free(array_iterator->iterator);
		free(array_iterator);
	}
}
