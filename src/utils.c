#include <string.h>
#include "malloc.h"
#include "utils.h"

char *object_strdup(const char *str)
{
	size_t len;
	char *s;

	len = strlen(str);
	s = object_malloc(sizeof(char) * (len+1));
	strcpy(s, str);

	return s;
}
