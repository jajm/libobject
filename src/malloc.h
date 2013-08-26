#ifndef object_malloc_h_included
#define object_malloc_h_included

#include <stdlib.h>

void *
object_malloc(
	size_t size
);

void *
object_calloc(
	size_t nmemb,
	size_t size
);

void *object_realloc(
	void *ptr,
	size_t size
);

#endif /* ! object_malloc_h_included */

