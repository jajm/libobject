#include <stdio.h>
#include "object.h"
#include "array.h"
#include "array_iterator.h"
#include "hash.h"
#include "integer.h"
#include "real.h"
#include "boolean.h"
#include "string.h"
#include "dumper.h"

int main()
{
	object_t *object;

	object = integer_new(22);
	dump(object);
	integer_free(object);

	object = array(string("aa"), string("bb"), string("cc"));
	dump(object);
	array_free(object, string_free, NULL);

	object = hash(
		"foo", array(integer_new(1), integer_new(2)),
		"bar", real(3.3),
		"baz", boolean_new(true),
	);
	dump(object);
}
