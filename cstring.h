//clang -std=c23 main.c && ./a.out
#pragma once
#include <string.h>

#define VSTRING_EMPTY			(vstring) { .data = "", .size = 0 }
#define BSTRING_EMPTY			(bstring) { .data = "", .size = 0 }
#define CSTRING_ERROR_NOT_FOUND		((size_t) - 1)
#define CSTRING_ERROR_NOT_ENOUGH_SPACE	1

//@struct vstring
//@desc string in memory self aware of it's size through `size`, should only be modifiable through `vstring_*` functions
typedef struct {
	const char* data;
	size_t size;
} vstring;

//@const BSTRING_SIZE 
//@desc Max size of a `bstring`
#define CSTRING_BSTRING_SIZE 256

//@struct bstring
//@desc helper struct to manipulate string data
typedef struct {
	char data[CSTRING_BSTRING_SIZE];
	size_t size;
} bstring;

//@function vstring_from
//@type HELPER
//@desc takes char* string and transforms it into a `vstring`
static inline vstring vstring_from(const char* str) {
	if (str == NULL) return VSTRING_EMPTY;
	return (vstring) {
		.data = str,
		.size = strlen(str),
	};
}

//@function vstring_compare
//@type HELPER
//@desc compares `a` and `b` to see which is larger
//@return 0 both are completly equal
//@return 1 `a` is larger
//@return 2 `b` is larger
static inline size_t vstring_compare(const vstring* a, const vstring* b) {
	if (a == NULL && b == NULL) return 0;
	if (b == NULL) return 1;
	if (a == NULL) return 2;
	if (a->size != b->size)
		return a->size > b->size ? 1 : 2;
	for (size_t i = 0; i < a->size; i++)
		if (a->data[i] != b->data[i])
			return a->data[i] > b->data[i] ? 1 : 2;
	return 0;
}

//@function vstring_equals
//@type HELPER
//@desc compares if `str` and `cstr` are exactly equal
static inline bool vstring_equals(const vstring* str, const char* cstr) {
	if (str == NULL && (cstr == NULL || cstr[0] == '\0')) return true;
	if (str == NULL || (cstr == NULL || cstr[0] == '\0')) return false;
	if (str->size != strlen(cstr)) return false;
	for (size_t i = 0; i < str->size; i++)
		if (cstr[i] != str->data[i]) return false;
	return true;
}

//@function vstring_get_char
//@type HELPER
//@return character in `str` at position `i`
static inline char vstring_get_char(const vstring* str, const size_t i) {
	if (str == NULL) return '\0';
	if (i >= str->size) return '\0';
	return str->data[i];
}

//@func vstring_remove_left
//@description removes `size` characters from the left of `str`, if can't trim it does nothing
static inline void vstring_remove_left(vstring* str, size_t size) {
	if (str == NULL) return;
	if (size > str->size) size = str->size;
	if (str->size == 0) return;
	str->size -= size;
	str->data += size;
}

//@func vstring_remove_right
//@description removes `size` characters from the right of `str`, if can't trim it does nothing
static inline void vstring_remove_right(vstring* str, size_t size) {
	if (str == NULL) return;
	if (size > str->size) size = str->size;
	if (str->size == 0) return;
	str->size -= size;
}

//@func vstring_duplicate
//@description creates a copy with `size` characters from the right of `str`
static inline vstring vstring_duplicate(vstring* str) {
	if (str == NULL) return VSTRING_EMPTY;
	if (str->size == 0) return VSTRING_EMPTY;
	char new_str[str->size];
	strncpy(new_str, str->data, str->size);
	return (vstring) {
		.data = new_str,
		.size = str->size
	};
}

//@func vstring_copy_left
//@description creates a copy with `size` characters from the left of `str`
static inline vstring vstring_copy_left(vstring* str, size_t size) {
	if (str == NULL) return VSTRING_EMPTY;
	if (size > str->size) size = str->size;
	if (str->size == 0 || size == 0) return VSTRING_EMPTY;
	char new_str[str->size];
	strncpy(new_str, str->data, str->size);
	return (vstring) {
		.data = new_str,
		.size = size
	};
}

//@func vstring_copy_right
//@description creates a copy with `size` characters from the right of `str`
static inline vstring vstring_copy_right(vstring* str, size_t size) {
	if (str == NULL) return VSTRING_EMPTY;
	if (size > str->size) size = str->size;
	if (str->size == 0 || size == 0) return VSTRING_EMPTY;
	char new_str[str->size];
	strncpy(new_str, str->data + str->size - size, str->size);
	return (vstring) {
		.data = new_str,
		.size = size
	};
}

//@func vstring_copy_left
//@description creates a copy of `str` with `size` characters after `start` characters (exclusive)
//@return `VSTRING_EMPTY` `str->size` or `size` == 0, also if `start` == `str->size`
static inline vstring vstring_copy_after(vstring* str, size_t start, size_t size) {
	if (str == NULL) return VSTRING_EMPTY;
	if (str->size == 0 || size == 0 || start >= str->size) return VSTRING_EMPTY;
	if (start + size > str->size) size = str->size - start;
	char new_str[str->size];
	strncpy(new_str, str->data + start, size);
	return (vstring) {
		.data = new_str,
		.size = size
	};
}

//@func vstring_has_prefix
//@desc checks if `str` starts with `prefix`
//@return `true` if `prefix` size == 0
//@return `false` if `str` size == 0
static inline bool vstring_has_prefix(const vstring* str, const vstring* prefix) {
	if (prefix->size == 0) return true;
	if (str->size == 0) return false;
	for (size_t i = 0; i < prefix->size; i++)
		if (str->data[i] != prefix->data[i])
			return false;
	return true;
}

//@func vstring_has_suffix
//@desc checks if `str` starts with `suffix`
//@return `true` if `suffix` size == 0
//@return `false` if `str` size == 0
static inline bool vstring_has_suffix(vstring* str, vstring* suffix) {
	if (suffix->size == 0) return true;
	if (str->size == 0) return false;
	for (size_t i = 0; i < suffix->size; i++)
		if (str->data[str->size - suffix->size + i] != suffix->data[i])
			return false;
	return true;
}

//@func vstring_find
//@return position of the first ocurrence of `search` inside of `str`
//@return `CSTRING_ERROR_NOT_FOUND`
static inline size_t vstring_find_first(vstring* str, vstring* search) {
	if (search->size == 0) return 0;
	if (str->size == 0) return CSTRING_ERROR_NOT_FOUND;
	for (size_t i = 0; i < str->size; i++) {
		if (str->data[i] == search->data[0]) {
			for (size_t search_i = 0; search_i < search->size; search_i++) {
				if (str->data[i] != search->data[search_i]) continue;
			}
			return i;
		}
	}
	return CSTRING_ERROR_NOT_FOUND;
}

//@func bstring_is_full
//@return if `size` *would* overflow the `CSTRING_BSTRING_SIZE` constant
static inline bool bstring_is_full(const size_t size) {
	return size >= CSTRING_BSTRING_SIZE;
}


//@func bstring_from
//@desc preffered method to init `bstring`
//@return new `bstring` struct
static inline bstring bstring_from(const char* str) {
	if (bstring_is_full(strlen(str))) return BSTRING_EMPTY;
	bstring builder = { .size = strlen(str) };
	strncat(builder.data, str, builder.size);
	return builder;
}

//@func bstring_concat
//@desc copies `str` data into `builder`
//@return error code `CSTRING_ERROR_NOT_ENOUGH_SPACE`
static inline char bstring_concat(bstring* builder, const vstring* str) {
	if (bstring_is_full(builder->size + str->size)) return CSTRING_ERROR_NOT_ENOUGH_SPACE;
	strncat(builder->data, str->data, str->size);
	builder->size += str->size;
	return 0;
}

//@func bstring_join
//@param str: array of `vstring`s
//@param str_count: array `str` count
//@param separator: `vstring` to put in the middle of `str` value
//@desc copies `str` data into `builder`
//@return error code `CSTRING_ERROR_NOT_ENOUGH_SPACE`
static inline char bstring_join(bstring* builder, const vstring str[], const size_t str_count, const vstring* separator) {
	for (size_t i = 0; i < str_count; i++) {
		if (i != 0) bstring_concat(builder, separator);
		bstring_concat(builder, &str[i]);
	}
	return 0;
}
