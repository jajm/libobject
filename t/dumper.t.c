#include <stdio.h>
#include "object.h"
#include "array.h"
#include "hash.h"
#include "integer.h"
#include "real.h"
#include "boolean.h"
#include "string.h"
#include "dumper.h"
#include "type.h"
#include "tap.h"

int main()
{
	object_t *object;
	string_t *s;

	plan(3);

	object = integer_new(22);
	s = dump(object);
	str_eq(string_to_c_str(s), "object = integer(22);");
	object_free(s);
	object_free(object);

	object = array(string("aa"), string("bb"), string("cc"));
	s = dump(object);
	str_eq(string_to_c_str(s),
		"object = array(\n"
		"  string(\"aa\"),\n"
		"  string(\"bb\"),\n"
		"  string(\"cc\"),\n"
		");");
	object_free(s);
	object_free(object);

	object = hash(
		"foo", array(
			integer_new(1),
			integer_new(2),
			real(3.3),
			boolean_new(true),
		)
	);
	s = dump(object);
	str_eq(string_to_c_str(s),
		"object = hash(\n"
		"  \"foo\", array(\n"
		"    integer(1),\n"
		"    integer(2),\n"
		"    real(3.300000),\n"
		"    boolean(true),\n"
		"  ),\n"
		");");
	object_free(s);
	object_free(object);

	types_finalize();
}
