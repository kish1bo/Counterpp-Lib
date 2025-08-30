#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream> 
#include "counterpp.h"

int main() {
	std::cout << counterpp::trygonometry::integrate([](double x) { return sin(x); }, 0.0, 3.141592653589793, 1000) << std::endl;
	return 0;
}