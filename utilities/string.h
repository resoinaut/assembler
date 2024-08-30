#pragma once

// implements String and Vector_String

#include "vector.h"

#define String               Vector_char

#define String_length        Vector_char_length

#define String_error_message Vector_char_error_message

#define String_init          Vector_char_init
#define String_free          Vector_char_free

#define String_append        Vector_char_append

IMPLEMENT_VECTOR(String)
