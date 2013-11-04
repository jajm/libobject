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

#ifndef object_dumper_h_included
#define object_dumper_h_included

#include "object.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

string_t * object_dump(object_t *object, const char *name);

#define dump(var) \
	object_dump(var, #var)

#ifdef __cplusplus
}
#endif

#endif /* ! object_dumper_h_included */

