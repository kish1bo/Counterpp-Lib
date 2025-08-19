#include "counterpp.h"

int add(int first_val, int second_val) {
	return first_val + second_val;
}

int sub(int first_val, int second_val) {
	return first_val - second_val;
}

double sin(int sin_val) {
	double normalize(double sin_val);
    sin_val = normalize(sin_val);
    double term = sin_val;   
    double out = sin_val;
    for (int n = 1; n < 10; n++) {
        term *= -1 * sin_val * sin_val / ((2 * n) * (2 * n + 1));
        out += term;
    }
    return out;
}