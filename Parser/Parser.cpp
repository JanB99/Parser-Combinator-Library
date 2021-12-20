#include "Parser.h"

Result parser(std::string input, std::regex reg) {

	Result res;
	if (input.empty()) {
		res.unconsumed = input;
		return res;
	}

	std::string sub = input.substr(0, 1);
	if (std::regex_match(sub, reg)) {
		res.consumed = sub;
		res.unconsumed = input.substr(1);
		return res;
	}

	return { "", input };
}

Result p_digit(std::string input) {
	return parser(input, std::regex("[0-9]"));
}

Result p_digits(std::string input) {
	return some(input, p_digit);
}

Result p_letter(std::string input) {
	return parser(input, std::regex("[a-z]"));
}

Result p_letters(std::string input) {
	return some(input, p_letter);
}

Result p_char(std::string input, std::regex reg) {
	return parser(input, reg);
}

Result some(std::string input, Result(*parser)(std::string)) {

	std::string cons;
	std::string uncons = input;

	while (!uncons.empty()) {
		Result res = (*parser)(uncons);
		if (uncons.compare(res.unconsumed) == 0) break;
		uncons = res.unconsumed;
		cons.append(res.consumed);
	}

	return { cons, uncons };
}

Result sequence(std::string input, std::vector<Result(*)(std::string)> parsers) {
	std::string cons;
	std::string uncons = input;

	for (Result(*parser)(std::string) : parsers) {
		Result res = (*parser)(uncons);

		if (res.consumed.empty()) {
			// return niks of foutmelding
			return { "", input};
		}

		uncons = res.unconsumed;
		cons.append(res.consumed);

	}

	return { cons, uncons };
}

Result choice(std::string input, Result(*a)(std::string), Result(*b)(std::string)) {
	Result res = (*a)(input);
	if (res.consumed.empty()) {
		res = (*b)(input);
		return res;
	}
	else {
		return res;
	}
}

Result choice(std::string input, std::vector<Result(*)(std::string)> parsers, Result(*b)(std::string)) {
	Result res = sequence(input, parsers);
	if (res.consumed.empty()) {
		res = (*b)(input);
		return res;
	}
	else {
		return res;
	}
}

Result choice(std::string input, Result(*a)(std::string), std::vector<Result(*)(std::string)> parsers) {
	Result res = (*a)(input);
	if (res.consumed.empty()) {
		res = sequence(input, parsers);
		return res;
	}
	else {
		return res;
	}
}


void print_result(Result res) {
	std::cout << "consumed: " << res.consumed << "\nunconsumed: " << res.unconsumed << std::endl;
}