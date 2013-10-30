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

#ifndef object_iterator_h_included
#define object_iterator_h_included

typedef struct iterator_s iterator_t;

typedef int (*iterator_reset_cb)(void *);
typedef int (*iterator_step_cb)(void *);
typedef object_t * (*iterator_get_cb)(void *);
typedef void * (*iterator_getkey_cb)(void *);
typedef void (*iterator_free_cb)(void *);

iterator_t *
iterator_new(
	void *data,
	iterator_reset_cb reset_cb,
	iterator_step_cb step_cb,
	iterator_get_cb get_cb,
	iterator_getkey_cb getkey_cb,
	iterator_free_cb free_cb
);

int iterator_reset(iterator_t *it);
int iterator_step(iterator_t *it);
object_t * iterator_get(iterator_t *it);
void * iterator_getkey(iterator_t *it);
void iterator_free(iterator_t *it);

#endif /* ! object_iterator_h_included */

