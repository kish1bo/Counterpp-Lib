#pragma once
#define FAST_MODE
#define CONST_PI 3.14159265358979323846
#define CONST_E 2.71828182845904523536
#define CONST_GOLDEN_RATIO 1.618033988749895
#define CONST_EPSILON 1e-10
#define COUNTERPP_VERSION "1.0.0"
#define COUNTERPP_FAST_MATH

namespace counterpp {
	namespace trygonometry{
		constexpr double PI = CONST_PI;
		constexpr double E = CONST_E;
		constexpr double EPSILON = 1e-10;
		constexpr double GOLDEN_RATIO = 1.618033988749895;
		double sin(int val);
		double cos(int val);
		double tan(int val);
	}
	namespace interpolation {
		double linear(double x0, double y0, double x1, double y1, double x);
		double bilinear(double x, double y, double x0, double y0, double x1, double y1, double q11, double q12, double q21, double q22);
		double cubic(double p0, double p1, double p2, double p3, double t);
	}
	namespace statistics
	{
		int mean(int* arr, int size);
		double median(int* arr, int size);
		int mode(int* arr, int size);
		double variance(int* arr, int size);
		double standard_deviation(int* arr, int size);
		int frequency(int* arr, int size, int val);
	}
	namespace inline_asm {
		int add(int first_val, int second_val);
		int sub(int first_val, int second_val);
		double normalize(double x);
		double log(int base, int number);
		double sqrt(double x, double guess = 1.0);
		double exp(double x);
	}
	namespace bitwise {
		int and_op(int a, int b);
		int or_op(int a, int b);
		int xor_op(int a, int b);
		int not_op(int a);
		int left_shift(int a, int n);
		int right_shift(int a, int n);
	}
}
