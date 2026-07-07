#include "../../cstring.h"
#include <stdio.h>

bool check(int expected[], int output[], size_t size) {
	bool result = true;
	for (size_t i = 0; i < size; i++)
		if (expected[i] != output[i]) {
			printf("Error at output %zu:\n\tExpected:\t%d\n\tOutput:\t\t%d\n\n", i, expected[i], output[i]);
			result = false;
			
		}
	return result;
}

int main(void) {
	const size_t size = 3;
	int expected[] = {0, 1, 3};
	int output[size];

	vstring a = vstring_from("hello");
	vstring b = vstring_from("hello");
	output[0] = vstring_compare(&a, &b);

	b.size = 4;
	output[1] = vstring_compare(&a, &b);

	vstring_remove_left(&a, 1);
	output[2] = vstring_compare(&a, &b);
	check(expected, output, size);
}
