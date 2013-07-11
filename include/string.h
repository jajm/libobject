#ifndef object_string_h_included
#define object_string_h_included

#include "object.h"

typedef object_t string_t;

string_t *
string_new(
	const char *s
);

string_t *
string_new_nocopy(
	char *s
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
string_cat(
	string_t *dest,
	unsigned int n,
	const char *src[]
);

int
string_scat(
	string_t *dest,
	unsigned int n,
	const string_t *src[]
);

void
string_free(
	string_t *string
);

int
object_is_string(
	const object_t *object
);

#endif /* ! object_string_h_included */

