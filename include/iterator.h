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

