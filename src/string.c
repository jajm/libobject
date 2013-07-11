#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "exception.h"
#include "object.h"
#include "string.h"

typedef struct {
	size_t len;
	char *c_str;
} string_value_t;

string_value_t * string_value_new(const char *s)
{
	string_value_t *string_value = NULL;
	size_t len;

	if (s != NULL) {
		string_value = malloc(sizeof(string_value_t));
		if (string_value == NULL) {
			object_throw_malloc_error(sizeof(string_value_t));
		}
		len = strlen(s);
		string_value->len = len;
		string_value->c_str = malloc(sizeof(char) * (len + 1));
		if (string_value->c_str == NULL) {
			free(string_value);
			object_throw_malloc_error(sizeof(char) * (len + 1));
		}
		strncpy(string_value->c_str, s, string_value->len + 1);
	}

	return string_value;
}

string_value_t * string_value_new_nocopy(char *s)
{
	string_value_t *string_value = NULL;

	if (s != NULL) {
		string_value = malloc(sizeof(string_value_t));
		if (string_value == NULL) {
			object_throw_malloc_error(sizeof(string_value_t));
		}
		string_value->len = strlen(s);
		string_value->c_str = s;
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

string_t * string_new(const char *s)
{
	string_value_t *string_value;
	string_t *string = NULL;

	string_value = string_value_new(s);
	if (string_value != NULL) {
		string = object_new(string_type, string_value);
		if (string == NULL) {
			log_error("Failed to create string object");
			string_value_free(string_value);
		}
	}

	return string;
}

string_t * string_new_nocopy(char *s)
{
	string_value_t *string_value;
	string_t *string = NULL;

	string_value = string_value_new_nocopy(s);
	if (string_value != NULL) {
		string = object_new(string_type, string_value);
		if (string == NULL) {
			log_error("Failed to create string object");
			string_value_free(string_value);
		}
	}

	return string;
}

string_t * string_new_from_array(unsigned int n, const char *s[])
{
	size_t len[n], total_len = 0, offset = 0;
	unsigned int i;
	char *buf;
	string_t *string;

	for (i=0; i<n; i++) {
		len[i] = strlen(s[i]);
		total_len += len[i];
	}

	buf = malloc(sizeof(char) * (total_len + 1));
	if (buf == NULL) {
		object_throw_malloc_error(sizeof(char) * (total_len + 1));
	}

	strncpy(buf, s[0], len[0]+1);
	offset = len[0];
	for (i=1; i<n; i++) {
		strncat(buf + offset, s[i], len[i]);
		offset += len[i];
	}

	string = string_new_nocopy(buf);

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

int string_cat(string_t *dest, unsigned int n, const char *src[])
{
	size_t len[n], total_len = 0;
	unsigned int i;
	string_value_t *string_value;

	for (i=0; i<n; i++) {
		len[i] = strlen(src[i]);
		total_len += len[i];
	}

	string_value = object_value(dest);
	string_value->c_str = realloc(string_value->c_str,
		string_value->len + total_len + 1);

	for (i=0; i<n; i++) {
		strcat(string_value->c_str, src[i]);
	}

	return total_len;
}

int string_scat(string_t *dest, unsigned int n, const string_t *src[])
{
	const char *s[n];
	unsigned int i;

	for (i=0; i<n; i++) {
		s[i] = string_to_c_str(src[i]);
	}

	return string_cat(dest, n, s);
}

void string_free(string_t *string)
{
	assert_object_is_string(string);
	object_free(string, string_value_free, NULL);
}

int object_is_string(const object_t *object)
{
	if (object_isa(object, string_type))
		return 1;

	return 0;
}
