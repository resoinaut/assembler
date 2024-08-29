#pragma once

#include "ansi.c"

#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

// note: empty color definitions will still print an ansi reset

#define TITLE_COLOR ANSI_BRIGHT_YELLOW

#define ERROR_COLOR ANSI_RED
#define ISSUE_COLOR

#define RESET_COLOR ANSI_RESET

void report_title(const char *title) {
	// example: `report_title("nas assembler v. alpha 0.0.0");`

	printf(TITLE_COLOR "%s" RESET_COLOR "\n", title);
}

void report_error(const char *error) {
	// example: `report_error("too many arguments");`

	printf(ERROR_COLOR "error: %s" RESET_COLOR "\n", error);
}

void report_issue(const char *issue, ...) {
	// example: `report_issue("expected 1 and received %i", argc - 1);`

	va_list args;
	va_start(args, issue);

	// renders lowercase the first character in case the issue is derived from strerror
	printf(ISSUE_COLOR "issue: %c" RESET_COLOR, tolower(issue[0]));
	vprintf(&issue[1], args);
	putchar('\n');

	va_end(args);
}
