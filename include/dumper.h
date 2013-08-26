#ifndef object_dumper_h_included
#define object_dumper_h_included

#include "object.h"
#include "string.h"

string_t * object_dump(object_t *object, const char *name);

#define dump(var) \
	object_dump(var, #var)

#endif /* ! object_dumper_h_included */

