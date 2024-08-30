#pragma once

#include "../utilities/string.h"
#include "../utilities/vector.h"

typedef struct {
	String type;
	String name;
	Vector_String args;
} Token;

IMPLEMENT_VECTOR(Token)
