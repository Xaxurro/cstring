#include "../../cstring.h"
#include <assert.h>

int main(void) {
	//original[12] = !
	char* original_str = "Hello World!";
	vstring str = vstring_from(original_str);

	//`size` < `str.size`
	vstring copy = vstring_copy_right(&str, 6);
	assert(copy.size == 6);

	char* expected_str = "World!";
	for (size_t i = 0; i < 6; i++)
		assert(vstring_get_char(&copy, i) == expected_str[i]);

	//`size` > `str.size`
	copy = vstring_copy_right(&str, 20);
	assert(copy.size == 12);

	expected_str = "Hello World!";
	for (size_t i = 0; i < 13; i++)
		assert(vstring_get_char(&copy, i) == expected_str[i]);

	//`size` == 0
	copy = vstring_copy_right(&str, 0);
	assert(copy.data[0] == '\0');
	assert(copy.size == 0);

	//NULL
	copy = vstring_copy_right(NULL, 1);
	assert(copy.data[0] == '\0');
	assert(copy.size == 0);
}
