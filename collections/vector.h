#pragma once

#include <sal.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_VECTOR(T)                                                                               \
                                                                                                       \
typedef struct {                                                                                       \
	T *_array;                                                                                         \
																				                       \
	size_t _length;                                                                                    \
	size_t _capacity;                                                                                  \
} Vector_##T;                                                                                          \
                                                                                                       \
void Vector_##T##_init(_Out_   Vector_##T *vector);                                                    \
void Vector_##T##_free(_Inout_ Vector_##T *vector);                                                    \
                                                                                                       \
/** @returns NULL on realloc failure. Use strerror(errno) for error message. */                        \
_Check_return_ _Success_(return) size_t Vector_##T##_append(_Inout_  Vector_##T *vector, T element);   \
                                                                                                       \
/** @returns NULL on realloc failure. Use strerror(errno) for error message. */                        \
_Check_return_ _Success_(return) size_t _Vector_##T##_resize(_Inout_ Vector_##T *vector);              \
																				                       \
void Vector_##T##_init(_Out_   Vector_##T *vector) {                                                   \
	vector->_array    = NULL;                                                                          \
	vector->_length   = 0;                                                                             \
	vector->_capacity = 0;                                                                             \
}                                                                                                      \
																				                       \
void Vector_##T##_free(_Inout_ Vector_##T *vector) {                                                   \
	free(vector->_array);                                                                              \
																				                       \
	vector->_array    = NULL;                                                                          \
	vector->_length   = 0;                                                                             \
	vector->_capacity = 0;                                                                             \
}                                                                                                      \
                                                                                                       \
_Check_return_ _Success_(return)                                                                       \
bool Vector_##T##_append(_Inout_ Vector_##T *vector, _In_ T element) {                                 \
	if (vector->_length == vector->_capacity) {                                                        \
		bool success = _Vector_##T##_resize(vector);                                                   \
		if (!success) return NULL;                                                                     \
	}                                                                                                  \
																				                       \
	vector->_array[vector->_length++] = element;                                                       \
	return true;                                                                                       \
}                                                                                                      \
																				                       \
_Check_return_ _Success_(return)                                                                       \
bool _Vector_##T##_resize(_Inout_ Vector_##T *vector) {                                                \
	vector->_capacity = vector->_capacity ? vector->_capacity * 2 : 1;                                 \
	vector->_array    = realloc(vector->_array, vector->_capacity * sizeof(T));                        \
                                                                                                       \
	return vector->_array;                                                                             \
}                                                                                                      \

// comment is here to prevent `backslash-newline at end of file` warning
