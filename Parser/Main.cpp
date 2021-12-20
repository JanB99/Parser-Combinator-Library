#include <iostream>
#include "ArithmeticParser.h"

int main(int argc, char* argv[]) {

	Result r;
	r = expr("500+10+80*(6+4*7)");
	
	print_result(r);

	
	return 0;
}