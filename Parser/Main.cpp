#include <iostream>
#include "Parser.h"

int main(int argc, char* argv[]) {

	Result r;
	
	r = sequence("5plus2", { p_digits, p_letters, p_digits });
	print_result(r);

	return 0;
}