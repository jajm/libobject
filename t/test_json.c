#include <stdio.h>
#include "json.h"

int main()
{
	object_t *object;
	const char json[] = "['a', 'b', 'c', {'d': 'e', 'f': 'g'}]";

	object = object_from_json(json);
	printf("%s\r        \n", object_type(object));
}
