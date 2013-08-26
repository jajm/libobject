#include <stdlib.h>
#include "malloc.h"
#include "exception.h"

void * object_malloc(size_t size)
{
	void *p;

	p = malloc(size);
	if (p == NULL)
		object_throw_malloc_error(size);

	return p;
}

void * object_calloc(size_t nmemb, size_t size)
{
	void *p;

	p = calloc(nmemb, size);
	if (p == NULL)
		object_throw_malloc_error(nmemb * size);

	return p;
}

void *object_realloc(void *ptr, size_t size)
{
	void *p;

	p = realloc(ptr, size);
	if (p == NULL)
		object_throw_malloc_error(size);

	return p;
}
