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

#include "object.h"
#include "malloc.h"
#include "iterator.h"

struct iterator_s {
	void *data;
	iterator_reset_cb reset_cb;
	iterator_step_cb step_cb;
	iterator_get_cb get_cb;
	iterator_getkey_cb getkey_cb;
	iterator_free_cb free_cb;
};

iterator_t * iterator_new(void *data, iterator_reset_cb reset_cb,
	iterator_step_cb step_cb, iterator_get_cb get_cb,
	iterator_getkey_cb getkey_cb, iterator_free_cb free_cb)
{
	iterator_t *it;

	it = object_malloc(sizeof(iterator_t));

	it->data = data;
	it->reset_cb = reset_cb;
	it->step_cb = step_cb;
	it->get_cb = get_cb;
	it->getkey_cb = getkey_cb;
	it->free_cb = free_cb;

	return it;
}

int iterator_reset(iterator_t *it)
{
	if (it == NULL) {
		return -1;
	}

	return it->reset_cb(it->data);
}

int iterator_step(iterator_t *it)
{
	if (it == NULL) {
		return -1;
	}

	return it->step_cb(it->data);
}

object_t * iterator_get(iterator_t *it)
{
	if (it == NULL) {
		return NULL;
	}

	return it->get_cb(it->data);
}

void * iterator_getkey(iterator_t *it)
{
	if (it == NULL) {
		return NULL;
	}

	return it->getkey_cb(it->data);
}

void iterator_free(iterator_t *it)
{
	if (it != NULL) {
		it->free_cb(it->data);
		free(it);
	}
}

