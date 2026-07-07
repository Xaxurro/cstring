#include "../../cstring.h"
#include <assert.h>
int main(void) {
	// Correct usage
	char* text = "hello";
	vstring str = vstring_from(text);
	assert(vstring_equals(&str, text));

	// Different text
	text = "hell";
	assert(!vstring_equals(&str, text));

	// Null Terminator in the middle
	text = "hell\0o";
	assert(!vstring_equals(&str, text));

	// Different `str` size
	str.size = 4;
	assert(vstring_equals(&str, text));

	// NULL
	assert(!vstring_equals(NULL, text));
	assert(vstring_equals(NULL, NULL));
	assert(vstring_equals(NULL, ""));
}
