#pragma once

#include <cctype>   // tolower
#include <cerrno>   // errno
#include <cstdio>   // std::vprintf stderr
#include <vector>   // std::vector
#include <cstdarg>  // va_list va_start va_end
#include <cstring>  // std::strerror
#include <iostream> // std::cout

#include "ansi.cc"
#include "shell.cc"

namespace report {

// TODO: switch colours to defines

namespace colour {
	const char *const reset   = ansi::reset;

	const char *const title   = ansi::colour::bright::yellow;

	const char *const error   = ansi::colour::red;
	const char *const issue   = ansi::colour::bright::white;
	const char *const shell   = ansi::colour::bright::white;

	const char *const success = ansi::colour::green;
	const char *const failure = ansi::colour::red;
}

void title(const char *title, ...) {
	va_list  args;
	va_start(args, title);

	std::cout << colour::title;
	std::vprintf(title, args);
	std::cout << colour::reset << '\n';

	va_end(args);
}

void error(const char *error, ...) {
	va_list  args;
	va_start(args, error);

	std::cerr << colour::error << "error: ";
	std::vfprintf(stderr, error, args);
	std::cerr << colour::reset << '\n';

	va_end(args);
}

void issue(const char *issue, ...) {
	va_list  args;
	va_start(args, issue);

	std::cerr << colour::issue << "issue: ";
	std::vfprintf(stderr, issue, args);
	std::cerr << colour::reset << '\n';

	va_end(args);
}

void issue(errno_t errnum) {
	const char *issue = errnum ? std::strerror(errnum) : "unknown for no errno was set";
	std::cerr << colour::issue << "issue: " << static_cast<char>(tolower(issue[0])) << &issue[1] << colour::reset << '\n';
}

void shell(const std::vector<shell::Argument> &args) {
	std::cerr << colour::shell << "\n$      ";

	bool show_markings = false;

	std::string markings = "       ";

	for (const shell::Argument &arg : args) {
		std::cerr << arg.source << ' ';

		switch (arg.mark_rule)
		{
		case shell::MarkRule::success:
			markings += colour::success;
			markings.append(arg.source.length(), '^');
			markings += ' ';
			markings += colour::reset;
			show_markings = true;
			break;
		case shell::MarkRule::failure:
			markings += colour::failure;
			markings.append(arg.source.length(), '^');
			markings += ' ';
			markings += colour::reset;
			show_markings = true;
			break;
		case shell::MarkRule::none:
			markings.append(arg.source.length() + 1, ' ');
			break;
		}
	}

	std::cerr << colour::reset << '\n';

	if (show_markings) std::cout << markings << '\n';
}

}
