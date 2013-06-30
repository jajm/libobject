#ifndef object_array_h_included
#define object_array_h_included

#include "object.h"

object_t *
array_new(
	unsigned int size,
	void *values[]
);

#define array(...) ({ \
	void *__values[] = {__VA_ARGS__}; \
	array_new(sizeof(__values) / sizeof(void *), __values); \
})

void
array_push(
	object_t *object,
	void *value
);

void
array_unshift(
	object_t *object,
	void *value
);

void *
array_pop(
	object_t *object
);

void *
array_shift(
	object_t *object
);

unsigned int
array_size(
	object_t *object
);

void
array_free(
	object_t *object,
	void *callback,
	void *callback_data
);

int
object_is_array(
	object_t *object
);

#endif /* ! object_array_h_included */

