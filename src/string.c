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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "exception.h"
#include "type.h"
#include "malloc.h"
#include "object.h"
#include "utils.h"
#include "string.h"

typedef struct {
	char *c_str;
	size_t len;
	size_t size;
} string_value_t;

void string_value_adjust_size(string_value_t *sv, size_t size_needed)
{
	size_t new_size;

	if (sv != NULL && size_needed > 0) {
		new_size = (sv->size > 0) ? sv->size : 2;
		if (size_needed > sv->size) {
			while (new_size < size_needed) {
				new_size *= 2;
			}
		} else {
			while (new_size/2 > size_needed) {
				new_size /= 2;
			}
		}

		if (new_size != sv->size) {
			sv->c_str = object_realloc(sv->c_str, new_size);
			sv->size = new_size;
		}
	}
}

string_value_t * string_value_new(char *s, size_t len)
{
	string_value_t *string_value = NULL;

	if (s != NULL) {
		string_value = object_malloc(sizeof(string_value_t));
		string_value->len = (len > 0) ? len : strlen(s);
		string_value->c_str = s;
		string_value->size = 0;
		string_value_adjust_size(string_value, string_value->len+1);
	}

	return string_value;
}

string_value_t * string_value_new_copy(const char *s)
{
	string_value_t *string_value = NULL;
	char *copy;
	size_t len;

	if (s != NULL) {
		len = strlen(s);
		copy = object_malloc(sizeof(char) * (len+1));
		strncpy(copy, s, len+1);
		string_value = string_value_new(copy, len);
	}

	return string_value;
}

void string_value_free(string_value_t *string_value)
{
	if (string_value != NULL) {
		free(string_value->c_str);
		free(string_value);
	}
}

static const char string_type[] = "STRING";

#define assert_object_is_string(object) \
	if (!object_is_string(object)) \
		object_throw_bad_type(object, string_type)

static _Bool string_type_registered = false;

char *string_to_str(const string_t *string);

void string_type_register(void)
{
	type_t *type;

	if (!string_type_registered) {
		type = type_get(string_type);
		type_set_callback(type, "free", string_value_free);
		type_set_callback(type, "to_str", string_to_str);
		string_type_registered = true;
	}
}

string_t * string_new(const char *s)
{
	string_value_t *string_value;
	string_t *string = NULL;

	string_type_register();

	string_value = string_value_new_copy(s);
	if (string_value != NULL) {
		string = object_new(string_type, string_value);
	}
	if (string == NULL) {
		log_error("Failed to create string object");
		string_value_free(string_value);
	}

	return string;
}

string_t * string_new_nocopy(char *s)
{
	string_value_t *string_value;
	string_t *string = NULL;

	string_type_register();

	string_value = string_value_new(s, strlen(s));
	if (string_value != NULL) {
		string = object_new(string_type, string_value);
	}
	if (string == NULL) {
		log_error("Failed to create string object");
		string_value_free(string_value);
	}

	return string;
}

string_t * string_new_from_array(unsigned int n, const char *s[])
{
	size_t len[n], total_len = 0, offset = 0;
	unsigned int i;
	char *buf;
	string_value_t *string_value;
	string_t *string;

	string_type_register();

	for (i=0; i<n; i++) {
		len[i] = strlen(s[i]);
		total_len += len[i];
	}

	buf = object_malloc(sizeof(char) * (total_len + 1));

	strncpy(buf, s[0], len[0]+1);
	offset = len[0];
	for (i=1; i<n; i++) {
		strncat(buf + offset, s[i], len[i]);
		offset += len[i];
	}

	string_value = string_value_new(buf, total_len);
	if (string_value != NULL) {
		string = object_new(string_type, string_value);
	}
	if (string == NULL) {
		log_error("Failed to create string object");
		string_value_free(string_value);
	}

	return string;
}

const char * string_to_c_str(const string_t *string)
{
	string_value_t *string_value = NULL;

	assert_object_is_string(string);

	string_value = object_value(string);
	return string_value->c_str;
}

size_t string_length(const string_t *string)
{
	string_value_t *string_value = NULL;

	assert_object_is_string(string);

	string_value = object_value(string);
	return (string_value != NULL) ? string_value->len : 0;
}

int string_cat_from_array(string_t *dest, unsigned int n, const char *src[])
{
	size_t len[n], total_len = 0;
	unsigned int i, offset;
	string_value_t *string_value;

	string_value = object_value(dest);
	if (string_value != NULL) {
		for (i=0; i<n; i++) {
			len[i] = strlen(src[i]);
			total_len += len[i];
		}

		string_value_adjust_size(string_value, string_value->len + total_len + 1);

		offset = string_value->len;
		for (i=0; i<n; i++) {
			strcat(string_value->c_str + offset, src[i]);
			offset += len[i];
		}
		string_value->len += total_len;
	}

	return total_len;
}

int string_scat_from_array(string_t *dest, unsigned int n, const string_t *src[])
{
	const char *s[n];
	unsigned int i;

	for (i=0; i<n; i++) {
		s[i] = string_to_c_str(src[i]);
	}

	return string_cat_from_array(dest, n, s);
}

void string_free(string_t *string)
{
	object_free(string);
}

int object_is_string(const object_t *object)
{
	if (object_isa(object, string_type))
		return 1;

	return 0;
}

char *string_to_str(const string_t *string)
{
	return object_strdup(string_to_c_str(string));
}
