#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream> 
#include "counterpp.h"

int main() {
	int x = 6; int y = 9;
	std::cout << counterpp::bitwise::and_op(x, y) << std::endl;
	return 0;
}