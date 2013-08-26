#include <stdio.h>
#include "real.h"
#include "type.h"
#include "tap.h"

int main()
{
	real_t *r;

	plan(3);

	r = real_new(42.42);
	ok(42.42 == real_get(r), "real_get(real_new(42.42)) == 42.42");
	real_set(r, 21.000001);
	ok(21.000001 == real_get(r), "real_set(r, 21.000001); real_get(r) == 21.000001");
	ok(object_is_real(r), "object_is_real(r)");

	real_free(r);

	types_finalize();

	return 0;
}
