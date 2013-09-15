#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "exception.h"
#include "type.h"
#include "malloc.h"
#include "object.h"
#include "real.h"

static const char real_type[] = "REAL";

#define assert_object_is_real(object) \
	if (!object_is_real(object)) \
		object_throw_bad_type(object, real_type)

static _Bool real_type_registered = false;

void real_type_register(void)
{
	type_t *type;

	if (!real_type_registered) {
		type = type_get(real_type);
		type_set_callback(type, "free", free);
		real_type_registered = true;
	}
}

real_t * real_new(double value)
{
	real_t *real;
	double *value_p;

	real_type_register();

	value_p = object_malloc(sizeof(double));
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

double real_get(const real_t *real)
{
	double *value_p;

	assert_object_is_real(real);

	value_p = object_value(real);
	return *value_p;
}

void real_free(real_t *real)
{
	assert_object_is_real(real);
	object_free(real);
}

int object_is_real(const object_t *object)
{
	if (object_isa(object, real_type))
		return 1;
	
	return 0;
}
