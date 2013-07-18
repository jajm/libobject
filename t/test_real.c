#include <stdio.h>
#include "real.h"

int main()
{
	real_t *d;

	d = real_new(42.42);
	printf("42.42 = %lf\n", real_get(d));
	real_set(d, 21.000001);
	printf("21.000001 = %lf\n", real_get(d));
	printf("is_real = %d\n", object_is_real(d));
	real_free(d);

	return 0;
}
