#pragma once

#include <sal.h>
#include <stddef.h>
#include <stdbool.h>

#include "token.h"
#include "tokenizer.h"
#include "../collections/string.c"

_Check_return_ _Success_(return)
bool Lexer_tokenize(_In_reads_bytes_(length) const char *line, _In_ size_t length, _Out_ Vector_Lexer_Token *tokens) {
	String buffer;
	String_init(&buffer);

	for (size_t i = 0; i < length; i++) {
		const char ch = line[i];

		size_t success = String_append(&buffer, ch);
		if (!success) return false;
	}

	String_free(&buffer);
}
