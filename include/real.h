#ifndef object_real_h_included
#define object_real_h_included

#include "object.h"

typedef object_t real_t;

real_t *
real_new(
	double value
);

#define real(value) \
	real_new(value)

void
real_set(
	real_t *real,
	double value
);

double
real_get(
	const real_t *real
);

void
real_free(
	real_t *real
);

int
object_is_real(
	const object_t *object
);

#endif /* ! object_real_h_included */

