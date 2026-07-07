#include "../../cstring.h"
#include <assert.h>

int main(void) {
	vstring str = vstring_from("Hello World!");
	// Get a normal character
	assert(vstring_get_char(&str, 5) == ' ');

	// Get Null Terminator
	assert(vstring_get_char(&str, 12) == '\0');

	// Get get over the char* string
	assert(vstring_get_char(&str, 13) == '\0');

	// Get get over `size` value
	str.size = 5;
	assert(vstring_get_char(&str, 6) == '\0');

	// NULL
	assert(vstring_get_char(NULL, 4) == '\0');
}
