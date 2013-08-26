#ifndef object_json_h_included
#define object_json_h_included

#include "object.h"

object_t *
object_from_json(
	const char *json
);

object_t *
object_from_json_file(
	const char *filename
);

#define OBJECT_TO_JSON_PLAIN 0
#define OBJECT_TO_JSON_SPACED (1 << 0)
#define OBJECT_TO_JSON_PRETTY (1 << 1)
#define OBJECT_TO_JSON_NOZERO (1 << 2)
#define OBJECT_TO_JSON_VERY_PRETTY \
	(OBJECT_TO_JSON_SPACED|OBJECT_TO_JSON_PRETTY|OBJECT_TO_JSON_NOZERO)

char *
object_to_json(
	object_t *object,
	int flags
);

#endif /* ! object_json_h_included */

