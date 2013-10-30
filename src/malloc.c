/*
 * Copyright 2013 Julian Maurice
 *
 * This file is part of libobject
 *
 * libobject is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libobject is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libobject.  If not, see <http://www.gnu.org/licenses/>.
 */

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
