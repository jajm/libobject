#ifndef object_array_iterator_h_included
#define object_array_iterator_h_included

typedef struct array_iterator_s array_iterator_t;

array_iterator_t *
array_iterator_new(
	const object_t *object
);

int
array_iterator_reset(
	array_iterator_t *array_iterator
);

int
array_iterator_step(
	array_iterator_t *array_iterator
);

object_t *
array_iterator_get(
	array_iterator_t *array_iterator
);

void
array_iterator_free(
	array_iterator_t *array_iterator
);

#define array_foreach(array, object) \
	for (array_iterator_t *__it = array_iterator_new(array) \
		; __it != NULL \
		; array_iterator_free(__it), __it = NULL) \
	while (!array_iterator_step(__it)) \
	for (object_t *object = array_iterator_get(__it), *__b = 0; __b == 0; \
		__b = (object_t *)1)

#endif /* ! object_array_iterator_h_included */

