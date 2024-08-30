#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "report.c"
#include "lexer/tokenizer.h"
#include "utilities/vector.h"

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

	Vector_Token tokens;
	Vector_Token_init(&tokens);

	const size_t read_count = fread(buffer, sizeof(char), BUFFER_SIZE, file);

	if (ferror(file) != 0) {
		report_error("cannot read file");
		report_issue(strerror(errno));

		fclose(file);
		return EXIT_FAILURE;
	}

	int exit_code = EXIT_SUCCESS;

	size_t start = 0;

	for (size_t i = 0; i < read_count; i++) {
		if (buffer[i] != '\n') continue;

		bool success = tokenize(&tokens, &buffer[start], &buffer[i] - &buffer[start]);
		
		if (!success) {
			report_error("cannot tokenize source");
			exit_code = EXIT_FAILURE;
			goto exit;
		}

		start = i + 1;
	}

	buffer[read_count] = '\0';
	printf(buffer);

	exit:

	fclose(file);
	Vector_Token_free(&tokens);

	return exit_code;
}
