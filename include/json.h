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

char *
object_to_json(
	object_t *object
);

#endif /* ! object_json_h_included */

