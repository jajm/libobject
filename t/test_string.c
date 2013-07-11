#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main()
{
	string_t *string = string("hello", ", ", "world!");
	printf("%s\n", string_to_c_str(string));

	string_cat(string, "foo", "bar", "baz");
	printf("%s\n", string_to_c_str(string));

	string_t *string2 = string("goodbye", ", ", "world...");
	string_scat(string, string2);
	printf("%s\n", string_to_c_str(string));

	string_free(string);
	string_free(string2);

	return 0;
}
