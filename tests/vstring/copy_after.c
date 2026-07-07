#include "../../cstring.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	//original[12] = !
	char* original_str = "Hello World!";
	vstring str = vstring_from(original_str);

	// Correct Usage
	vstring copy = vstring_copy_after(&str, 6, 5);
	char* expected_str = "World";
	assert(copy.size == 5);
	for (size_t i = 0; i < copy.size; i++)
		assert(copy.data[i] == expected_str[i]);

	//`start + size` > `str.size`
	copy = vstring_copy_after(&str, 6, 10);
	expected_str = "World!";
	assert(copy.size == 6);
	for (size_t i = 0; i < copy.size; i++)
		assert(copy.data[i] == expected_str[i]);

	//`start` > `str.size`
	copy = vstring_copy_after(&str, 20, 1);
	assert(copy.size == 0);
	assert(copy.data[0] == '\0');
	
	//`size` == 0
	copy = vstring_copy_after(&str, 6, 0);
	assert(copy.size == 0);
	assert(copy.data[0] == '\0');

	// NULL
	copy = vstring_copy_after(NULL, 6, 5);
	assert(copy.size == 0);
	assert(copy.data[0] == '\0');
}
