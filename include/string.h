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

#ifndef object_string_h_included
#define object_string_h_included

#include <stdlib.h>
#include "object.h"

typedef object_t string_t;

string_t *
string_new(
	const char *s
);

string_t *
string_new_from_array(
	unsigned int n,
	const char *s[]
);

#define string(...) ({ \
	const char *__args[] = { __VA_ARGS__ }; \
	string_new_from_array(sizeof(__args) / sizeof(*__args), __args); \
})

const char *
string_to_c_str(
	const string_t *string
);

size_t
string_length(
	const string_t *string
);

int
string_cat_from_array(
	string_t *dest,
	unsigned int n,
	const char *src[]
);

#define string_cat(dest, ...) ({ \
	const char *__args[] = { __VA_ARGS__ }; \
	string_cat_from_array(dest, sizeof(__args) / sizeof(*__args), __args); \
})

int
string_scat_from_array(
	string_t *dest,
	unsigned int n,
	const string_t *src[]
);

#define string_scat(dest, ...) ({ \
	const string_t *__args[] = { __VA_ARGS__ }; \
	string_scat_from_array(dest, sizeof(__args) / sizeof(*__args), __args); \
})

void
string_free(
	string_t *string
);

int
object_is_string(
	const object_t *object
);

#endif /* ! object_string_h_included */

