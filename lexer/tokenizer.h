#pragma once

#include <sal.h>
#include <stdbool.h>

#include "token.h"

/** @returns False on failure. Use strerror(errno) for error message. */
_Check_return_ _Success_(return) bool Lexer_tokenize(_In_reads_bytes_(length) const char *line, _In_ size_t length, _Out_ Vector_Lexer_Token *tokens);

#include "tokenizer.c"
