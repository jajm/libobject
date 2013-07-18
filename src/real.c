#include <stdio.h>
#include <stdlib.h>
#include "exception.h"
#include "object.h"
#include "real.h"

static const char real_type[] = "REAL";

#define assert_object_is_real(object) \
	if (!object_is_real(object)) \
		object_throw_bad_type(object, real_type)

real_t * real_new(double value)
{
	real_t *real;
	double *value_p;

	value_p = malloc(sizeof(double));
	if (value_p == NULL) {
		object_throw_malloc_error(sizeof(double));
	}
	*value_p = value;

	real = object_new(real_type, value_p);
	return real;
}

void real_set(real_t *real, double value)
{
	double *value_p;

	assert_object_is_real(real);

	value_p = object_value(real);
	*value_p = value;
}

double real_get(real_t *real)
{
	double *value_p;

	assert_object_is_real(real);

	value_p = object_value(real);
	return *value_p;
}

void real_free(real_t *real)
{
	if (object_is_real(real)) {
		object_free(real, free, NULL);
	}
}

int object_is_real(object_t *object)
{
	if (object_isa(object, real_type))
		return 1;
	
	return 0;
}
