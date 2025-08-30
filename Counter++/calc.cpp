#include "counterpp.h"
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
namespace counterpp
{
    int add(int first_val, int second_val) {
        return first_val + second_val;
    }

    int sub(int first_val, int second_val) {
        return first_val - second_val;
    }

    constexpr double sqrt(double x, double guess = 1.0) {
        return ((guess * guess - x) < 1e-12 && (guess * guess - x) > -1e-12)
            ? guess
            : sqrt(x, 0.5 * (guess + x / guess));
    }
    namespace trygonometry
    {
        double normalize(double x) {
            if (x == 0) {
                throw std::invalid_argument("Input cannot be zero for function.");
                return 0;
            }
            while (x > counterpp::trygonometry::PI) x -= 2 * counterpp::trygonometry::PI;
            while (x < -counterpp::trygonometry::PI) x += 2 * counterpp::trygonometry::PI;
            return x;
        }

        double sin(int sin_val) {
            if (sin_val == 0) {
                throw std::invalid_argument("Input cannot be zero for function.");
                return 0;
            }
            normalize(sin_val);
            sin_val == normalize(sin_val);
            double term = sin_val;
            double out = sin_val;
            for (int n = 1; n < 10; n++) {
                term *= -1 * sin_val * sin_val / ((2 * n) * (2 * n + 1));
                out += term;
            }
            return out;
        }

        double cos(int cos_val) {
            if (cos_val == 0) {
                throw std::invalid_argument("Input cannot be zero for function.");
                return 0;
            }
            double normalize(double cos_val);
            cos_val = normalize(cos_val);
            double term = 1;
            double out = 1;
            for (int n = 1; n < 10; n++) {
                term *= -1 * cos_val * cos_val / ((2 * n - 1) * (2 * n));
                out += term;
            }
            return out;
        }

        double tan(int tan_val) {
            if (tan_val == 0) {
                throw std::invalid_argument("Input cannot be zero for function.");
                return 0;
            }
            double normalize(double tan_val);
            tan_val = normalize(tan_val);
            return sin(tan_val) / cos(tan_val);
        }

    }
    namespace inline_asm
    {
        
        double log(int base, int number) {
            if (base <= 1 || number <= 0) {
                throw std::invalid_argument("Base must be greater than 1 and number must be positive.");
            }
            return std::log(number) / std::log(base);
        }

        double exp(double x) {
            if (x == 0) {
                return 1.0;
            }
            double term = 1.0;
            double sum = 1.0;
            for (int n = 1; n < 20; n++) {
                term *= x / n;
                sum += term;
            }
            return sum;
        }
	}
   
    namespace statistics {
        int mean(int* arr, int size) {
            if (size <= 0) {
                throw std::invalid_argument("Array size must be positive.");
            }
            int sum = 0;
            for (int i = 0; i < size; i++) {
                sum += arr[i];
            }
            return sum / size;
        }

        int mode(int* arr, int size) {
            if (size <= 0) {
                throw std::invalid_argument("Array size must be positive.");
            }
            int maxValue = arr[0];
            int maxCount = 0;
            for (int i = 0; i < size; ++i) {
                int count = 0;
                for (int j = 0; j < size; ++j) {
                    if (arr[j] == arr[i]) ++count;
                }
                if (count > maxCount) {
                    maxCount = count;
                    maxValue = arr[i];
                }
            }
            return maxValue;
        }

        int frequency(int* arr, int size, int val) {
            if (size <= 0) {
                throw std::invalid_argument("Array size must be positive.");
            }
            int count = 0;
            for (int i = 0; i < size; i++) {
                if (arr[i] == val) {
                    count++;
                }
            }
            return count;
        }

        double median(int* arr, int size) {
            if (size <= 0) {
                throw std::invalid_argument("Array size must be positive.");
            }
            int* sorted = new int[size];
            for (int i = 0; i < size; i++) {
                sorted[i] = arr[i];
            }
            std::sort(sorted, sorted + size);
            double median;
            if (size % 2 == 0) {
                median = (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
            }
            else {
                median = sorted[size / 2];
            }
            delete[] sorted;
            return median;
        }

        double variance(int* arr, int size) {
            if (size <= 0) {
                throw std::invalid_argument("Array size must be positive.");
            }
            double mean_val = static_cast<double>(mean(arr, size));
            double sum = 0.0;
            for (int i = 0; i < size; i++) {
                sum += (arr[i] - mean_val) * (arr[i] - mean_val);
            }
            return sum / size;
        }

        double standard_deviation(int* arr, int size) {
            if (size <= 0) {
                throw std::invalid_argument("Array size must be positive.");
            }
            return sqrt(variance(arr, size));
        }
    }
    namespace interpolation
    {
        double linear(double x0, double y0, double x1, double y1, double x) {
            if (x1 - x0 == 0) {
                throw std::invalid_argument("x0 and x1 cannot be the same value.");
            }
            return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
        }
        double bilinear(double x, double y, double x0, double y0, double x1, double y1, double q11, double q12, double q21, double q22) {
            if (x1 - x0 == 0 || y1 - y0 == 0) {
                throw std::invalid_argument("x0 and x1 cannot be the same value and y0 and y1 cannot be the same value.");
            }
            return (q11 * (x1 - x) * (y1 - y) +
                q21 * (x - x0) * (y1 - y) +
                q12 * (x1 - x) * (y - y0) +
                q22 * (x - x0) * (y - y0)) /
                ((x1 - x0) * (y1 - y0));
        }
        double cubic(double p0, double p1, double p2, double p3, double t) {
            return p1 + 0.5 * t * (p2 - p0 +
                t * (2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3 +
                    t * (3.0 * (p1 - p2) + p3 - p0)));
        }
    }
    namespace bitwise
    {
        int and_op(int a, int b) {
            return a & b;
        }
        int or_op(int a, int b) {
            return a | b;
        }
        int xor_op(int a, int b) {
            return a ^ b;
        }
        int not_op(int a) {
            return ~a;
        }
        int left_shift(int a, int n) {
            return a << n;
        }
        int right_shift(int a, int n) {
            return a >> n;
        }
    }
}