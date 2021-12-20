#pragma once
#include <iostream>
#include <string>
#include <regex>

/// <summary>
/// Result struct containing: 
/// 1. The string that was consumed by the parser; and 
/// 2. The string that was unconsumed by the parser
/// </summary>
typedef struct {
	std::string consumed;
	std::string unconsumed;
} Result;

void print_result(Result res);

// Generic parser that accepts an input based on a regular expression match
Result parser(std::string input, std::regex reg);

// digit parser [0-9]
Result p_digit(std::string input);
Result p_digits(std::string input);

// letter parser [a-z]
Result p_letter(std::string input);
Result p_letters(std::string input);

// specific character parser
Result p_char(std::string input, char c);

// some (consumes as much as possible based on specified parser)
// sequence (consumes specified sequence of input based on parser)
Result some(std::string input, Result(*parser)(std::string));
Result sequence(std::string input, std::vector<Result(*)(std::string)> parsers);

// either one or the other parser
Result choice(std::string input, Result(*a)(std::string), Result(*b)(std::string));
Result choice(std::string input, std::vector<Result(*)(std::string)> parsers, Result(*b)(std::string));
Result choice(std::string input, Result(*a)(std::string), std::vector<Result(*)(std::string)> parsers);