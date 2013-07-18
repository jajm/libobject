#ifndef object_dumper_h_included
#define object_dumper_h_included

void object_dump(object_t *object, const char *name);

#define dump(var) \
	object_dump(var, #var)

#endif /* ! object_dumper_h_included */

