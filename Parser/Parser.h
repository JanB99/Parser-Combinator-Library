#pragma once
#include <iostream>
#include <string>
#include <regex>

typedef struct {
	std::string consumed;
	std::string unconsumed;
} Result;

void print_result(Result res);

Result parser(std::string input, std::regex reg);

Result p_digit(std::string input);
Result p_digits(std::string input);

Result p_letter(std::string input);
Result p_letters(std::string input);

Result p_char(std::string input, std::regex reg);

Result some(std::string input, Result(*parser)(std::string));
Result sequence(std::string input, std::vector<Result(*)(std::string)> parsers);

Result choice(std::string input, Result(*a)(std::string), Result(*b)(std::string));
Result choice(std::string input, std::vector<Result(*)(std::string)> parsers, Result(*b)(std::string));
Result choice(std::string input, Result(*a)(std::string), std::vector<Result(*)(std::string)> parsers);