#pragma once

#include <sal.h>
#include <stdbool.h>

#include "token.h"

_Check_return_ _Success_(return) bool tokenize(
	_Out_              Vector_Token *tokens,
	_In_reads_(length) const char   *line,
	_In_ size_t                      length
);

#include "tokenizer.c"
