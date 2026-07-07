#include "cstring.h"
#include <stdio.h>

int main (void) {
	vstring array[] = {
		vstring_from("Hola"),
		vstring_from("me"),
		vstring_from("llamo"),
		vstring_from("Xaxurro"),
	};
	bstring builder = bstring_from("");
	vstring separator = vstring_from(" ");
	bstring_join(&builder, array, sizeof(array) / sizeof(vstring), &separator);
	printf("str: \"%s\"\n", builder.data);
	printf("count: %zu", builder.size);
}
