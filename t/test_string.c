#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main()
{
	string_t *string = string("hello", ", ", "world!");
	printf("%s\n", string_to_c_str(string));
	string_free(string);

	return 0;
}
