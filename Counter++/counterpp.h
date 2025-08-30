#pragma once
#define FAST_MODE 
#define CONST_PI 3.14159265358979323846
#define CONST_E 2.71828182845904523536
#define CONST_GOLDEN_RATIO 1.618033988749895
#define CONST_EPSILON 1e-10
#define COUNTERPP_VERSION "1.0.2"
#define COUNTERPP_FAST_MATH

#include <string>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>

namespace counterpp {
	enum class KeyType {
		Letters, //Only Letters in key
		Numbers, //Only Numbers in key
		Mixed //Mix of Letters and Numbers in key
	};

	namespace trygonometry{
		constexpr double PI = CONST_PI;
		constexpr double E = CONST_E;
		constexpr double EPSILON = 1e-10;
		constexpr double GOLDEN_RATIO = 1.618033988749895;
		double normalize(double val); // Normalize angle to range [-PI, PI]
		double sin(double val); // Sine function
		double cos(double val); // Cosine function
		double tan(double val); // Tangent function
		int integrate(std::function<double(double)> f, double a, double b, int n); // Definite integral using the trapezoidal rule
	}
	namespace interpolation {
		double linear(double x0, double y0, double x1, double y1, double x); // Linear interpolation
		double bilinear(double x, double y, double x0, double y0, double x1, double y1, double q11, double q12, double q21, double q22); // Bilinear interpolation
		double cubic(double p0, double p1, double p2, double p3, double t); // Cubic interpolation
	}
	namespace statistics
	{
		int mean(int* arr, int size); //Mean of an array
		double median(int* arr, int size); //Median of an array
		int mode(int* arr, int size); //Mode of an array
		double variance(int* arr, int size); //Variance of an array
		double standard_deviation(int* arr, int size); //Standard Deviation of an array
		int frequency(int* arr, int size, int val); // Frequency of a value in an array
	}
	namespace inline_asm {
		int add(int first_val, int second_val); // Add two integers
		int sub(int first_val, int second_val); // Subtraction of two integers
		double log(int base, int number); // Logarithm with arbitrary base
		double sqrt(double x, double guess = 1.0); // Square root using Newton's method
		double exp(double x); // Exponential function e^x
	}
	namespace bitwise {
		constexpr int and_op(int a, int b); // Bitwise AND
		constexpr int or_op(int a, int b); // Bitwise OR 
		constexpr int xor_op(int a, int b); // Bitwise XOR
		constexpr int not_op(int a); // Bitwise NOT
		constexpr int left_shift(int a, int n); // Arithmetic left shift
		constexpr int right_shift(int a, int n); // Arithmetic right shift
	}
	namespace random {
		int rand_int(int min, int max); // Generate a random integer between min and max
		double rand_double(double min, double max); // Generate a random double between min and max
		std::string randomKey(KeyType type, int Length);// Generate a random key of specified type and length, types: Letters, Numbers, Mixed
		void seed(unsigned int seed); // Seed the random number generator
	}
}
