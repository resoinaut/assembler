#include <ios>       // std::ios
#include <cerrno>    // errno
#include <vector>    // std::vector
#include <cstddef>   // std::size_t
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <algorithm> // std::min

#include "ansi.cc"
#include "shell.cc"
#include "report.cc"

int main(int argc, char *argv[]) {
	putchar('\n');

	if (argc < 2) {
		report::title("nas assembler v. alpha 0.0.0");

		return 0;
	}

	if (argc > 2) {
		std::vector<shell::Argument> arguments = {
			shell::Argument(argv[0], shell::MarkRule::none),
			shell::Argument(argv[1], shell::MarkRule::success),
		};

		for (std::size_t i = 2; i < argc; i++)
			arguments.push_back(shell::Argument(argv[i], shell::MarkRule::failure));

		report::error("too many arguments");
		report::issue("expected 1 and recieved %i", argc - 1);
		report::shell(arguments);

		return 1;
	}

	std::ifstream file(argv[1], std::ios::in);

	if (!file) {
		report::error("failure opening file");
		report::issue(errno);

		return 1;
	}

	char buffer[5]; // 4096

	while (file) {
		file.read(buffer, sizeof(buffer));

		if (file.fail()) {
			report::error("failure reading file");
			report::issue(errno);

			file.close();

			return 1;
		}

		std::cout.write(buffer, std::min(sizeof(buffer), static_cast<size_t>(file.gcount())));
	}

	std::cout << ansi::cursor::up;

	file.close();

	return 0;
}
