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

#include "object.h"

/* Iterator reset callback.
 *
 * This callback is responsible for resetting the iterator to its initial state.
 *
 * Parameters
 *   data : The iterator data.
 *
 * Should returns
 *   0 on success.
 *   a negative value on failure.
 */
typedef int (*iterator_reset_cb)(void *data);

/* Iterator step callback.
 *
 * This callback should advance the iterator one step.
 *
 * Parameters
 *   data : The iterator data.
 *
 * Should returns
 *   0 on success.
 *   a positive value if iterator is already on last element.
 *   a negative value on failure.
 */
typedef int (*iterator_step_cb)(void *data);

/* Iterator get callback.
 *
 * This callback should return the object at iterator position.
 *
 * Parameters
 *   data : The iterator data.
 *
 * Should returns
 *   Pointer to object.
 */
typedef object_t * (*iterator_get_cb)(void *data);

/* Iterator getkey callback.
 *
 * This callback should return the key at iterator position, if any.
 *
 * Parameters
 *   data : The iterator data.
 *
 * Should returns
 *   Pointer to key if there is one, or NULL otherwise.
 */
typedef void * (*iterator_getkey_cb)(void *data);

/* Iterator free callback.
 *
 * This callback is responsible for freeing memory used by iterator data.
 *
 * Parameters
 *   data : The iterator data.
 */
typedef void (*iterator_free_cb)(void *data);

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new iterator.
 *
 * Parameters
 *   data      : Iterator data that will be passed to each callback.
 *   reset_cb  : Reset callback.
 *   step_cb   : Step callback.
 *   getkey_cb : Getkey callback.
 *   free_cb   : Free callback.
 *
 * Returns
 *   Pointer to iterator.
 */
iterator_t *
iterator_new(
	void *data,
	iterator_reset_cb reset_cb,
	iterator_step_cb step_cb,
	iterator_get_cb get_cb,
	iterator_getkey_cb getkey_cb,
	iterator_free_cb free_cb
);

/* Call iterator reset callback.
 *
 * Parameters
 *   it : Pointer to iterator.
 *
 * Returns
 *   The return value of iterator reset callback.
 */
int
iterator_reset(
	iterator_t *it
);

/* Call iterator step callback.
 *
 * Parameters
 *   it : Pointer to iterator.
 *
 * Returns
 *   The return value of iterator step callback.
 */
int
iterator_step(
	iterator_t *it
);

/* Call iterator get callback.
 *
 * Parameters
 *   it : Pointer to iterator.
 *
 * Returns
 *   The return value of iterator get callback.
 */
object_t *
iterator_get(
	iterator_t *it
);

/* Call iterator getkey callback.
 *
 * Parameters
 *   it : Pointer to iterator.
 *
 * Returns
 *   The return value of iterator getkey callback.
 */
void *
iterator_getkey(
	iterator_t *it
);

/* Free memory used by iterator.
 *
 * It calls iterator free callback.
 *
 * Parameters
 *   it : Pointer to iterator.
 */
void
iterator_free(
	iterator_t *it
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_iterator_h_included */

