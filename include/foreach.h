#ifndef object_foreach_h_included
#define object_foreach_h_included

#define foreach(object, value) \
	for (iterator_t *__it = object_iterator_new(object) \
		; __it != NULL \
		; iterator_free(__it), __it = NULL) \
	for (object_t *value = NULL; value == NULL; value = (object_t *)1) \
	while ( !iterator_step(__it)  \
	     && ((value = iterator_get(__it)) || (!value)) )

#define foreachk(object, key, value) \
	for (iterator_t *__it = object_iterator_new(object) \
		; __it != NULL \
		; iterator_free(__it), __it = NULL) \
	for (object_t *value = NULL; value == NULL; value = (object_t *)1) \
	for (void *key = NULL; key == NULL; key = (void *)1) \
	while ( !iterator_step(__it) \
	     && ((value = iterator_get(__it)) || (!value)) \
	     && ((key = iterator_getkey(__it)) || (!key)) )

#endif /* ! object_foreach_h_included */
