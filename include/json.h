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

#ifndef object_json_h_included
#define object_json_h_included

#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new object from JSON string.
 *
 * Parameters
 *   json : JSON string.
 *
 * Returns
 *   Pointer to object.
 */
object_t *
object_from_json(
	const char *json
);

/* Create a new object from a JSON file.
 *
 * Parameters
 *   filename : JSON file name.
 *
 * Returns
 *   Pointer to object.
 */
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

/* Create a JSON string from an object.
 *
 * Parameters
 *   object : Pointer to object.
 *   flags : OBJECT_TO_JSON_PLAIN, or a OR-ed combination of
 *           OBJECT_TO_JSON_SPACED, OBJECT_TO_JSON_PRETTY and
 *           OBJECT_TO_JSON_NOZERO
 *
 * Returns
 *   JSON string.
 */
char *
object_to_json(
	const object_t *object,
	int flags
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_json_h_included */

