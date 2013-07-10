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
	string_t *string
);

size_t
string_length(
	string_t *string
);

void
string_free(
	string_t *string
);

int
object_is_string(
	object_t *object
);

#endif /* ! object_string_h_included */

