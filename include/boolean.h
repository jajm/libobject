#ifndef object_boolean_h_included
#define object_boolean_h_included

#include <stdbool.h>
#include "object.h"

typedef object_t boolean_t;

boolean_t *
boolean_new(
	_Bool value
);

#define boolean(value) \
	boolean_new(value)

_Bool
boolean_get(
	boolean_t *boolean
);

void
boolean_set(
	boolean_t *boolean,
	_Bool value
);

void
boolean_free(
	boolean_t *boolean
);

int
object_is_boolean(
	object_t *object
);

#endif /* ! object_boolean_h_included */

