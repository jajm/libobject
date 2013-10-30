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

#ifndef object_object_h_included
#define object_object_h_included

typedef struct object_s object_t;

object_t *
object_new(
	const char *type,
	void *value
);

object_t *
object_new_ref(
	const char *type,
	void *value
);

object_t *
object_get_ref(
	object_t *object
);

const char *
object_type(
	const object_t *object
);

void *
object_value(
	const object_t *object
);

void object_set(
	object_t *object,
	void *value
);

int
object_isset(
	const object_t *object
);

int
object_isa(
	const object_t *object,
	const char *type
);

void
object_free(
	object_t *object
);

#endif /* ! object_object_h_included */

