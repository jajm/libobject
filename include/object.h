#ifndef object_object_h_included
#define object_object_h_included

typedef struct object_s object_t;

object_t *
object_new(
	const char *type,
	void *value
);

object_t *
object_new_ref(
	const char *type,
	void *value
);

object_t *
object_get_ref(
	object_t *object
);

const char *
object_type(
	const object_t *object
);

void *
object_value(
	const object_t *object
);

int
object_isset(
	const object_t *object
);

int
object_isa(
	const object_t *object,
	const char *type
);

void
object_free(
	object_t *object
);

#endif /* ! object_object_h_included */

