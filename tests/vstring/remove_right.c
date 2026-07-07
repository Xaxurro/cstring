#include "../../cstring.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	// Correct usage
	vstring str = vstring_from("Hello World!");
	vstring_remove_right(&str, 1);
	assert(vstring_get_char(&str, 11) == '\0');
	assert(str.size == 11);

	// Remove more than `str.size`
	str = vstring_from("Hello World!");
	vstring_remove_right(&str, 13);
	assert(vstring_get_char(&str, 0) == '\0');
	assert(str.size == 0);

	// NULL
	vstring_remove_left(NULL, 13);
	assert(true);
}
