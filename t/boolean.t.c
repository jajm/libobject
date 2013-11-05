#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "type.h"
#include "tap.h"

int main()
{
	boolean_t *boolean;
	char *str;

	plan(4);

	boolean = boolean_new(true);
	ok(boolean_get(boolean), "boolean is true");
	str = object_to_str(boolean);
	ok(!strcmp(str, "TRUE"), "object_to_str returns \"TRUE\"");
	free(str);

	boolean_set(boolean, false);
	ok(!boolean_get(boolean), "boolean is false");
	str = object_to_str(boolean);
	ok(!strcmp(str, "FALSE"), "object_to_str returns \"FALSE\"");
	free(str);

	boolean_free(boolean);

	types_finalize();

	return 0;
}
