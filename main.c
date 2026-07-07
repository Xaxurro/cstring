#include "cstring.h"
#include <stdio.h>

int main (void) {
	vstring array[] = {
		to_vstring("Hola"),
		to_vstring("me"),
		to_vstring("llamo"),
		to_vstring("Xaxurro"),
	};
	bstring builder = to_bstring("");
	vstring separator = to_vstring(" ");
	bstring_join(&builder, array, 4, &separator);
	printf("str: \"%s\"\n", builder.data);
	printf("count: %zu", builder.size);
}
