#pragma once

#include <stdlib.h>
#include "vector.h"

typedef struct {
	char *_array;

	size_t _length;
	size_t _capacity;
} String;

void String_init(_Out_   String *string);
void String_free(_Inout_ String *string);

/** @returns NULL on realloc failure. Use strerror(errno) for error message. */
_Check_return_ _Success_(return) size_t String_append(_Inout_ String *string, _In_ char character);

/** @returns NULL on realloc failure. Use strerror(errno) for error message. */
_Check_return_ _Success_(return) size_t _String_resize(_Inout_ String *string);

DEFINE_VECTOR(String)

#include "string.c"
