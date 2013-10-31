#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "type.h"
#include "tap.h"

int main()
{
	boolean_t *boolean;

	plan(2);

	boolean = boolean_new(true);
	ok(boolean_get(boolean), "boolean is true");
	boolean_set(boolean, false);
	ok(!boolean_get(boolean), "boolean is false");
	boolean_free(boolean);

	types_finalize();

	return 0;
}
