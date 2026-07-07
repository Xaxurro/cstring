#include "../../cstring.h"
#include <assert.h>

int main(void) {
	// NULL
	vstring str = vstring_from(NULL);
	assert(str.size == 0);
	assert(str.data[0] == '\0');

	// Empty string
	str = vstring_from("");
	assert(str.size == 0);
	assert(str.data[0] == '\0');

	// Regular string
	const char* text = "hello";
	str = vstring_from(text);
	assert(str.size == 5);
	for (size_t i = 0; i < strlen(text); i++)
		assert(str.data[i] == text[i]);

	// Null terminator in the middle
	str = vstring_from("hell\0o");
	assert(str.size == 4);
	assert(strlen(str.data) == 4);
}
