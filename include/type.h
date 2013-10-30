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

#ifndef object_type_h_included
#define object_type_h_included

typedef struct type_s type_t;

void types_initialize();

type_t *
type_get(
	const char *name
);

const char *
type_name(
	type_t *type
);

void
type_set_callback(
	type_t *type,
	const char *name,
	void *callback
);

void *
type_get_callback(
	type_t *type,
	const char *name
);

void types_finalize();

#endif /* ! object_type_h_included */

