#ifndef object_type_h_included
#define object_type_h_included

typedef struct type_s type_t;

void types_initialize();

type_t *
type_get(
	const char *name
);

const char *
type_name(
	type_t *type
);

void
type_set_callback(
	type_t *type,
	const char *name,
	void *callback
);

void *
type_get_callback(
	type_t *type,
	const char *name
);

void types_finalize();

#endif /* ! object_type_h_included */

