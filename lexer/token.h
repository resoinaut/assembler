#pragma once

#include "../collections/string.h"

struct {
	String type;
	String name;
	Vector_String args;
} Lexer_Token;

DEFINE_VECTOR(Lexer_Token)
