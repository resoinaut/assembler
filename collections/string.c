#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "string.h"

void String_init(_Out_   String *string) {
	string->_array    = NULL;
	string->_length   = 0;
	string->_capacity = 0;
}

void String_free(_Inout_ String *string) {
	free(string->_array);

	string->_array    = NULL;
	string->_length   = 0;
	string->_capacity = 0;
}

_Check_return_ _Success_(return) size_t String_append(_Inout_ String *string, _In_ char character) {
	if (string->_length == string->_capacity) {
		size_t success = _String_resize(string);
		if (!success) return NULL;
	}

	string->_array[string->_length++] = character;
}

_Check_return_ _Success_(return) size_t _String_resize(_Inout_ String *string) {
	string->_capacity = string->_capacity ? string->_capacity * 2 : 1;
	string->_array    = realloc(string->_array, string->_capacity);

	return string->_array;
}
