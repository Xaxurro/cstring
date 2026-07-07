#include "../../cstring.h"
#include <assert.h>

int main(void) {
	vstring a = vstring_from("hello");
	vstring b = vstring_from("hello");

	//Completly equal
	assert(vstring_compare(&a, &b) == 0);

	//Larger `a`, `b` has lower size
	b.size = 4;
	assert(vstring_compare(&a, &b) == 1);

	//Larger `b`, `b[0]` > `a[0]`
	vstring_remove_left(&a, 1);
	assert(vstring_compare(&a, &b) == 2);

	//Larger `b`, `a` has lower size
	a = vstring_from("abc\0def");
	b = vstring_from("abcdef");
	assert(vstring_compare(&a, &b) == 2);

	//NULL
	assert(vstring_compare(NULL, NULL) == 0);
	assert(vstring_compare(&a, NULL) == 1);
	assert(vstring_compare(NULL, &b) == 2);
}
