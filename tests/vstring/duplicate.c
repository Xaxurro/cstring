#include "../../cstring.h"
#include <assert.h>

int main(void) {
	//original[12] = !
	char* original_str = "Hello World!";
	vstring str = vstring_from(original_str);
	vstring copy = vstring_duplicate(&str);

	assert(str.size == copy.size);
	for (size_t i = 0; i < str.size; i++)
		assert(vstring_get_char(&str, i) == vstring_get_char(&copy, i));

	//null pointer
	vstring empty_str = vstring_duplicate(NULL);
	assert(empty_str.size == 0);
	assert(empty_str.data[0] == '\0');
}
