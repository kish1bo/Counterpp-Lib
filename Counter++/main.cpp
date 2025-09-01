#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream> 
#include "counterpp.h"
#include <chrono>
#include <ctime>
#include <thread>

int main() {
	int x = counterpp::bits::clearbit(4, 2);
	std::cout << x << std::endl;
} 