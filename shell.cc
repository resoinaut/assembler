#pragma once

namespace shell {

enum MarkRule {
	none,
	success,
	failure,
};

struct Argument {
	MarkRule mark_rule;
	std::string source;

	Argument(std::string source, MarkRule mark_rule = MarkRule::none)
	: source(source), mark_rule(mark_rule) {};
};

}
