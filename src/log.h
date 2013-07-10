#ifndef object_log_h_included
#define object_log_h_included

#include <stdlib.h>
#include <lll/lll.h>

#define object_log(level, level_str, ...) do { \
	char *verbosity_str = getenv("LIBOBJECT_VERBOSITY"); \
	int verbosity = verbosity_str ? atoi(verbosity_str) : 0; \
	if (level <= verbosity) { \
		lll_fprint(stderr, "[%T][libobject]?0|$0:|| %m at $1:$2 ($3)", \
			"%s", level_str, "%s", __FILE__, "%d", __LINE__, \
			"%s", __func__, NULL, NULL, __VA_ARGS__); \
	} \
} while(0)

#define log_fatal(...) \
	object_log(1, "fatal", __VA_ARGS__)

#define log_error(...) \
	object_log(2, "error", __VA_ARGS__)

#define log_warning(...) \
	object_log(3, "warning", __VA_ARGS__)

#define log_info(...) \
	object_log(4, "info", __VA_ARGS__)

#define log_debug(...) \
	object_log(5, "debug", __VA_ARGS__)


#endif /* ! object_log_h_included */

