//clang -std=c23 main.c && ./a.out
#pragma once
#include <string.h>
#include <stdio.h>

//@struct
//@desc string in memory self aware of it's size through `size`, should only be modifiable through `vstring_*` functions
typedef struct {
	const char* data;
	size_t size;
} vstring;

//@const BSTRING_SIZE 
//@desc Max size of a `bstring`
#define BSTRING_SIZE 256

//@struct bstring
//@desc helper struct to manipulate string data
typedef struct {
	char data[BSTRING_SIZE];
	size_t size;
} bstring;

//@func print_vstring
//@type DEBUG
//@desc prints a single vstring
static inline void print_vstring(vstring str) {
	for (size_t i = 0; i < str.size; i++) {
		putchar(str.data[i]);
	}
}

//@function to_vstring
//@type HELPER
//@desc takes char* string and transforms it into a `vstring`
static inline vstring to_vstring(const char* str) {
	return (vstring) {
		.data = str,
		.size = strlen(str),
	};
}

//@func vstring_trim_right
//@description removes `size` characters from the right of the `vstring`, if can't trim (overflow) does nothing
static inline void vstring_trim_right(vstring* string, size_t size) {
	if (size > string->size) size = string->size;
	if (string->size == 0) return;
	string->size -= size;
}

//@func
//@description removes `size` characters from the left of the `vstring`, if can't trim (overflow) does nothing
static inline void vstring_trim_left(vstring* string, size_t size) {
	if (size > string->size) size = string->size;
	if (string->size == 0) return;
	string->size -= size;
	string->data += size;
}

//@func
//@desc checks if `string` starts with `prefix`, note: returns `true` if `prefix` size == 0.
static inline bool vstring_has_prefix(vstring* string, vstring* prefix) {
	if (prefix->size == 0) return true;
	if (string->size == 0) return false;
	for (size_t i = 0; i < prefix->size; i++) if (string->data[i] != prefix->data[i]) return false;
	return true;
}

//@func
//@desc checks if `string` ends with `suffix`, note: returns `true` if `prefix` size == 0.
static inline bool vstring_has_suffix(vstring* string, vstring* suffix) {
	if (suffix->size == 0) return true;
	if (string->size == 0) return false;
	for (size_t i = 0; i < suffix->size; i++) {
		if (string->data[string->size - suffix->size + i] != suffix->data[i]) return false;
	}
	return true;
}

//@func to_bstring
//@desc returns a new `bstring` struct, preffered method to init
static inline bstring to_bstring(char* str) {
	bstring builder = { .size = strlen(str) };
	strncat(builder.data, str, builder.size);
	return builder;
}

//@func bstring_is_full
//@return if the size passed overflows the `BSTRING_SIZE` constant
static inline bool bstring_is_full(size_t size) {
	return size >= BSTRING_SIZE;
}

//@func
//@desc
//@return 1: not enough space in builder
static inline char bstring_concat(bstring* builder, vstring* str) {
	if (bstring_is_full(builder->size + str->size)) return 1;
	strncat(builder->data, str->data, str->size);
	builder->size += str->size;
	return 0;
}

//@func
//@desc
//@return 1: not enough space in builder
static inline char bstring_join(bstring* builder, vstring str[], size_t str_count, vstring* separator) {
	for (size_t i = 0; i < str_count; i++) {
		if (i != 0) bstring_concat(builder, separator);
		bstring_concat(builder, &str[i]);
	}
	return 0;
}
