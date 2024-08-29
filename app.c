#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "report.c"
#include "lexer/tokenizer.c"

// 4096 bytes (4KiB) is the most common OS page size
#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
	putchar('\n');

	if (argc < 2) {
		report_title("nas assembler v. alpha 0.0.0");
		return EXIT_SUCCESS;
	}

	if (argc > 2) {
		report_error("too many arguments");
		report_issue("expected 1 and received %i", argc - 1);
		return EXIT_FAILURE;
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL) {
		report_error("cannot open file");
		report_issue(strerror(errno));

		fclose(file);
		return EXIT_FAILURE;
	}

	char buffer[BUFFER_SIZE];

	const size_t read_count = fread(buffer, sizeof(char), BUFFER_SIZE, file);

	if (ferror(file) != 0) {
		report_error("cannot read file");
		report_issue(strerror(errno));

		fclose(file);
		return EXIT_FAILURE;
	}

	size_t end;

	for (size_t i = 0; i < read_count; i++) {
		if (buffer[i] == '\n') end = i;
	}

	buffer[read_count] = '\0';
	printf(buffer);

	fclose(file);

	return EXIT_SUCCESS;
}
