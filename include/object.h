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

#include "iterator.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Create a new object.
 *
 * An object is basically two things: a type and a value.
 * The type of an object describe what kind of data is stored in object's value.
 * It can be associated with callbacks to handle the different operations on
 * value that can be needed.
 * For example, a type may need a 'free' callback for the memory to be released
 * by object_free().
 *
 * Parameters
 *   type  : A unique string identifier of a type.
 *   value : Pointer to value.
 *
 * Returns
 *   Pointer to new object.
 */
object_t *
object_new(
	const char *type,
	void *value
);

/* Create a new object reference.
 *
 * An object reference is a regular object that is tagged as being a reference.
 * It means that the 'free' callback will not be called by object_free().
 *
 * Parameters
 *   type  : A unique string identifier of a type.
 *   value : Pointer to value.
 *
 * Returns
 *   Pointer to new object reference.
 */
object_t *
object_new_ref(
	const char *type,
	void *value
);

/* Create a new object reference from an existing object.
 *
 * Same as object_new_ref(), except that it takes an object as parameter.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   Pointer to new object reference.
 */
object_t *
object_get_ref(
	object_t *object
);

/* Get the type of an object.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   The unique string identifier of the object's type.
 */
const char *
object_type(
	const object_t *object
);

/* Get the value of an object.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   Pointer to value.
 */
void *
object_value(
	const object_t *object
);

/* Set the value of an object.
 *
 * Note that the 'free' callback is not called on current value.
 *
 * Parameters
 *   object : Pointer to object.
 *   value  : Pointer to new value.
 */
void object_set(
	object_t *object,
	void *value
);

/* Is the object set ?
 *
 * An object is considered as set if it has a type.
 * An object with a NULL value is considered as set.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   1 if object is set.
 *   0 otherwise.
 */
int
object_isset(
	const object_t *object
);

/* Test the type of an object.
 *
 * Parameters
 *   object : Pointer to object.
 *   type   : The string identifier of type to test against.
 *
 * Returns
 *   1 if object's type match the type given in parameters.
 *   0 otherwise.
 */
int
object_isa(
	const object_t *object,
	const char *type
);

/* Create a new iterator.
 *
 * This function call 'iterator' callback if it finds one.
 * Prototype of this callback should be:
 *   iterator_t *iterator(object_t *object);
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   Pointer to iterator if 'iterator' callback is found.
 *   NULL otherwise.
 */
iterator_t *
object_iterator_new(
	const object_t *object
);

/* Convert an object into string.
 *
 * This function call 'to_str' callback if it finds one.
 * Prototype of this callback should be:
 *   char *to_str(object_t *object);
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   String conversion of object if 'to_str' callback is found. User is
 *   responsible for freeing memory with free().
 *   NULL if 'to_str' callback is not found.
 */
char *
object_to_str(
	const object_t *object
);

/* Create a copy of an object.
 *
 * This function call 'copy' callback if it finds one?
 * Prototype of this callback should be:
 *   void * copy(const void *value);
 * It should returns a copy of object value.
 *
 * Parameters
 *   object : Pointer to object.
 *
 * Returns
 *   a copy of object if 'copy' callback is found. object_free() can be safely
 *   used on this copy.
 *   NULL if 'copy' callback is not found.
 */
object_t *
object_copy(
	const object_t *object
);

/* Free memory used by object.
 *
 * This function call 'free' callback if it finds one.
 * Prototype of this callback should be:
 *   void free(void *);
 *
 * Parameters
 *   object : Pointer to object.
 */
void
object_free(
	object_t *object
);

#ifdef __cplusplus
}
#endif

#endif /* ! object_object_h_included */

