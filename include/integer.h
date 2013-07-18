#ifndef object_integer_h_included
#define object_integer_h_included

#include "object.h"

typedef object_t integer_t;
typedef int integer_int_t;

integer_t *
integer_new(
	integer_int_t value
);

void
integer_set(
	integer_t *integer,
	integer_int_t value
);

integer_int_t
integer_get(
	integer_t *integer
);

void
integer_free(
	integer_t *integer
);

int
object_is_integer(
	object_t *object
);

#endif /* ! object_integer_h_included */

