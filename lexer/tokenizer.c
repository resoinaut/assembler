#pragma once

#include <sal.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include "token.h"
#include "tokenizer.h"
#include "../utilities/string.h"

_Check_return_ _Success_(return) bool tokenize(
	_Out_              Vector_Token *tokens,
	_In_reads_(length) const char   *line,
	_In_               size_t        length
) {
	String buffer;
	String_init(&buffer);

	for (size_t i = 0; i < length; i++) {
		const char ch = line[i];



		size_t success = String_append(&buffer, ch);
		if (!success) return false;
	}

	String_free(&buffer);
}
