#ifndef object_exception_h_included
#define object_exception_h_included

#include <libexception/exception.h>
#include "log.h"

#define object_throw(exception, message, ...) do { \
	log_fatal(message, ##__VA_ARGS__); \
	throw(exception, message, ##__VA_ARGS__); \
} while(0)

#define object_throw_malloc_error(size) \
	object_throw(NotEnoughMemoryException, "failed to allocate %d bytes", \
		size)

#define object_throw_bad_type(object, expected_type) \
	object_throw(BadTypeException, "Expected '%s', got '%s' (%s)", \
		expected_type, object_type(object), #object)


#endif /* ! object_exception_h_included */

