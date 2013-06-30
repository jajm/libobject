#ifndef object_object_h_included
#define object_object_h_included

typedef struct object_s object_t;

object_t *
object_new(
	const char *type,
	void *value
);

const char *
object_type(
	object_t *object
);

void *
object_value(
	object_t *object
);

int
object_set(
	object_t *object,
	const char *type,
	void *value
);

void
object_unset(
	object_t *object,
	void *callback,
	void *callback_data
);

int
object_isset(
	object_t *object
);

int
object_isa(
	object_t *object,
	const char *type
);

void
object_free(
	object_t *object,
	void *callback,
	void *callback_data
);

#endif /* ! object_object_h_included */

