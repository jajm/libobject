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
#include "array.h"

typedef object_t string_t;

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new string object from a copy of a null-terminated string.
 *
 * Parameters
 *   s : A null-terminated string.
 *
 * Returns
 *   Pointer to the new string object.
 */
string_t *
string_new(
	const char *s
);

/* Create a new string object from a substring.
 *
 * Parameters
 *   s : A null-terminated string.
 *   offset : Where the substring starts.
 *   length : How many characters in the substring.
 *
 * Returns
 *   Pointer to the new string object.
 */
string_t *
string_new_from_substring(
	const char *s,
	unsigned int offset,
	size_t length
);

/* Create a new string object from a null-terminated string.
 *
 * The null-terminated string will not be duplicated.
 *
 * Parameters
 *   s : A null-terminated string.
 *
 * Returns
 *   Pointer to the new string object.
 */
string_t *
string_new_nocopy(
	char *s
);

/* Create a new string object from an array of null-terminated strings.
 *
 * All string parameters will be duplicated.
 *
 * Parameters
 *   n : Number of elements in s.
 *   s : Array of null-terminated string.
 *
 * Returns
 *   Pointer to the new string object.
 */
string_t *
string_new_from_array(
	unsigned int n,
	const char *s[]
);

#define string(...) ({ \
	const char *__args[] = { __VA_ARGS__ }; \
	string_new_from_array(sizeof(__args) / sizeof(*__args), __args); \
})

/* Create a new string object from a substring.
 *
 * Parameters
 *   string : Pointer to string object.
 *   offset : Where the substring starts.
 *   length : How many characters in the substring.
 *
 * Returns
 *   Pointer to the new string object.
 */
string_t *
string_substring(
	const string_t *string,
	unsigned int offset,
	size_t length
);

/* Get the value of string object.
 *
 * Parameters
 *   string : Pointer to string object.
 *
 * Returns
 *   A null-terminated string which is the value of string object.
 */
const char *
string_to_c_str(
	const string_t *string
);

/* Get the length of string.
 *
 * Parameters
 *   string : Pointer to string object.
 *
 * Returns
 *   Length (number of characters) of string.
 */
size_t
string_length(
	const string_t *string
);

/* Concatenate an array of strings into a string object.
 *
 * Parameters
 *   dest : Pointer to string object.
 *   n    : Number of elements in src.
 *   src  : Array of null-terminated strings.
 *
 * Returns
 *   Number of characters added to string object.
 */
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

/* Concatenate an array of string objects into a string object.
 *
 * Parameters
 *   dest : Pointer to string object.
 *   n    : Number of elements in src.
 *   src  : Array of string objects.
 *
 * Returns
 *   Number of characters added to string object.
 */
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

/* Split a string object into multiple string objects.
 *
 * Parameters
 *   string : Pointer to string object.
 *   sep    : Separator character to split on.
 *
 * Returns
 *   An array of string objects.
 */
array_t *
string_split(
	const string_t *string,
	char sep
);

/* Tell if object is a string.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   0 if object is not a string.
 *   1 if object is a string.
 */
int
object_is_string(
	const object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_string_h_included */

