#ifndef object_array_h_included
#define object_array_h_included

#include "object.h"

typedef object_t array_t;

array_t *
array_new(
	unsigned int size,
	object_t *values[]
);

#define array(...) ({ \
	object_t *__values[] = {__VA_ARGS__}; \
	array_new(sizeof(__values) / sizeof(object_t *), __values); \
})

void
array_push(
	array_t *array,
	object_t *object
);

void
array_unshift(
	array_t *array,
	object_t *object
);

object_t *
array_pop(
	array_t *array
);

object_t *
array_shift(
	array_t *array
);

object_t *
array_get(
	array_t *array,
	unsigned int offset
);

void
array_splice(
	array_t *array,
	unsigned int offset,
	unsigned int length,
	void *callback,
	void *callback_data,
	array_t *replacement
);

array_t *
array_slice(
	array_t *array,
	unsigned int offset,
	unsigned int length,
	void *callback,
	void *callback_data
);

void
array_map(
	array_t *array,
	void *callback,
	void *callback_data
);

array_t *
array_filter(
	array_t *array,
	void *callback,
	void *callback_data
);

object_t *
array_reduce(
	array_t *array,
	void *callback,
	void *callback_data
);

unsigned int
array_size(
	array_t *array
);

void
array_free(
	array_t *array,
	void *callback,
	void *callback_data
);

int
object_is_array(
	object_t *object
);

#endif /* ! object_array_h_included */

