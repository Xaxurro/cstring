#include "../../cstring.h"
#include <assert.h>

int main(void) {
	// Correct usage
	vstring str = vstring_from("Hello World!");
	vstring_remove_left(&str, 11);
	assert(str.data[0] == '!');
	assert(str.size == 1);

	// Remove more than `str.size`
	str = vstring_from("Hello World!");
	vstring_remove_left(&str, 13);
	assert(str.data[0] == '\0');
	assert(str.size == 0);

	// NULL
	vstring_remove_left(NULL, 13);
	assert(true);
}
