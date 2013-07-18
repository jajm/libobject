#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

int main()
{
	boolean_t *boolean;

	boolean = boolean_new(true);
	printf("true = %d\n", boolean_get(boolean));
	boolean_set(boolean, false);
	printf("false = %d\n", boolean_get(boolean));
	boolean_free(boolean);

	return 0;
}
