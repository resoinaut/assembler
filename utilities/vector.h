#pragma once

#include <sal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

#define IMPLEMENT_VECTOR(T)                                                                            \
                                                                                                       \
typedef struct {                                                                                       \
	T *_array;                                                                                         \
																				                       \
	size_t _errnum;                                                                                    \
	size_t _length;                                                                                    \
	size_t _capacity;                                                                                  \
} Vector_##T;                                                                                          \
                                                                                                       \
inline size_t Vector_##T##_length(_In_ Vector_##T *vector);                                            \
                                                                                                       \
inline const char *Vector_##T##_error_message(_In_ Vector_##T *vector);                                \
                                                                                                       \
void Vector_##T##_init(_Out_ Vector_##T *vector);                                                      \
void Vector_##T##_free(_Out_ Vector_##T *vector);                                                      \
                                                                                                       \
_Check_return_ _Success_(return) bool Vector_##T##_append(_Inout_ Vector_##T *vector, _In_ T element); \
                                                                                                       \
_Check_return_ _Success_(return) bool _Vector_##T##_resize(_Inout_ Vector_##T *vector);                \
                                                                                                       \
inline size_t Vector_##T##_length(_In_ Vector_##T *vector) {                                           \
	return vector->_length;                                                                            \
}                                                                                                      \
                                                                                                       \
inline const char *Vector_##T##_error_message(_In_ Vector_##T *vector) {                               \
	return strerror(vector->_errnum);                                                                  \
}                                                                                                      \
																				                       \
void Vector_##T##_init(_Out_ Vector_##T *vector) {                                                     \
	vector->_array    = NULL;                                                                          \
	vector->_errnum   = 0;                                                                             \
	vector->_length   = 0;                                                                             \
	vector->_capacity = 0;                                                                             \
}                                                                                                      \
																				                       \
void Vector_##T##_free(_Out_ Vector_##T *vector) {                                                     \
	free(vector->_array);                                                                              \
																				                       \
	vector->_array    = NULL;                                                                          \
	vector->_errnum   = 0;                                                                             \
	vector->_length   = 0;                                                                             \
	vector->_capacity = 0;                                                                             \
}                                                                                                      \
                                                                                                       \
_Check_return_ _Success_(return) bool Vector_##T##_append(Vector_##T *vector, T element) {             \
	if (vector->_length == vector->_capacity) {                                                        \
		bool success = _Vector_##T##_resize(vector);                                                   \
		if (!success) return false;                                                                    \
	}                                                                                                  \
																				                       \
	vector->_array[vector->_length++] = element;                                                       \
	return true;                                                                                       \
}                                                                                                      \
																				                       \
_Check_return_ _Success_(return) bool _Vector_##T##_resize(Vector_##T *vector) {                       \
	vector->_capacity = vector->_capacity ? vector->_capacity * 2 : 1;                                 \
	vector->_array    = (T *) realloc(vector->_array, vector->_capacity * sizeof(T));                  \
                                                                                                       \
	if (vector->_array == NULL) vector->_errnum = errno;                                               \
	return vector->_array;                                                                             \
}                                                                                                      \

// primitive datatype vector implementations

IMPLEMENT_VECTOR(char)
