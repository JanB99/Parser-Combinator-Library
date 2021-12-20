#include "Parser.h"

/// <summary>
/// Generic building block parser
/// parses input based on regular expression match
/// </summary>
/// <param name="input">String to be parsed</param>
/// <param name="reg">regex to be used to match the input</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
Result parser(std::string input, std::regex reg) {

	Result res;
	if (input.empty()) {
		res.unconsumed = input;
		return res;
	}

	std::string firstChar = input.substr(0, 1);
	if (std::regex_match(firstChar, reg)) {
		res.consumed = firstChar;
		res.unconsumed = input.substr(1);
		return res;
	}

	return { "", input };
}

/// <summary>
/// A single digit [0-9] parser
/// </summary>
/// <param name="input">String to be parsed</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
Result p_digit(std::string input) {
	return parser(input, std::regex("[0-9]"));
}

/// <summary>
/// Digit [0-9] parser that consumes as many digits as possible
/// </summary>
/// <param name="input">String to be parsed</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
Result p_digits(std::string input) {
	return some(input, p_digit);
}

/// <summary>
/// A single letter [a-z] parser
/// </summary>
/// <param name="input">String to be parsed</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
Result p_letter(std::string input) {
	return parser(input, std::regex("[a-z]"));
}

/// <summary>
/// Letter [a-z] parser that consumes as many letters as possible
/// </summary>
/// <param name="input">String to be parsed</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
Result p_letters(std::string input) {
	return some(input, p_letter);
}

/// <summary>
/// A custom parser based on parsing a specific character
/// </summary>
/// <param name="input">String to be parsed</param>
/// <param name="c">Specific character to be used to parse input</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
Result p_char(std::string input, char c) {
	
	std::string specialChars = "^$\.*+?()[]{}|";
	std::string parseInput(1, c);
	if (specialChars.find(c) != std::string::npos) {
		parseInput.insert(0, "\\");
	}

	return parser(input, std::regex(parseInput));
}

/// <summary>
/// Consumes the input as many times possible 
/// based on the specified pointer to a parser function
/// </summary>
/// <param name="input">String to be parsed</param>
/// <param name="parser">Pointer to a parser function that returns a Result struct and accepts an input string as parameter</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
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

/// <summary>
/// Consumes the input in a sequence of specified parsers one after the other
/// </summary>
/// <param name="input">String to be parsed</param>
/// <param name="parsers">std::vector of ordered pointer parser functions containing an input string and returning a Result object</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
Result sequence(std::string input, std::vector<Result(*)(std::string)> parsers) {
	std::string cons;
	std::string uncons = input;

	for (Result(*parser)(std::string) : parsers) {
		Result res = (*parser)(uncons);

		if (res.consumed.empty()) {
			return { "", input};
		}

		uncons = res.unconsumed;
		cons.append(res.consumed);
	}

	return { cons, uncons };
}

/// <summary>
/// Consumes the input string based on either the first parser "a" or the second parser "b"
/// </summary>
/// <param name="input">String to be parsed</param>
/// <param name="a">Pointer to a parser function that returns a Result struct and accepts an input string as parameter</param>
/// <param name="b">Pointer to a parser function that returns a Result struct and accepts an input string as parameter</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
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

/// <summary>
/// Consumes the input string based on either the sequence of parsers "parsers" or another parser "b"
/// </summary>
/// <param name="input">String to be parsed</param>
/// <param name="parsers">std::vector of ordered pointer parser functions containing an input string and returning a Result object</param>
/// <param name="b">Pointer to a parser function that returns a Result struct and accepts an input string as parameter</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
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

/// <summary>
/// Consumes the input string based on either the parser "a" or a sequence of parsers "parsers"
/// </summary>
/// <param name="input">String to be parsed</param>
/// <param name="a">Pointer to a parser function that returns a Result struct and accepts an input string as parameter</param>
/// <param name="parsers">std::vector of ordered pointer parser functions containing an input string and returning a Result object</param>
/// <returns>Result struct containing the consumed string and unconsumed string</returns>
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