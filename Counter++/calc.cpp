#include "counterpp.h"
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>

namespace counterpp
{
    namespace inline_asm
    {
        int add(int first_val, int second_val) {
            return first_val + second_val;
        }

        int sub(int first_val, int second_val) {
            return first_val - second_val;
        }

        double sqrt(double x, double guess) {
            if (x < 0.0) {
                throw std::invalid_argument("Cannot compute square root of negative number.");
            }
            if (x == 0.0) return 0.0;
            double g = guess;
            for (int i = 0; i < 100; ++i) {
                double next = 0.5 * (g + x / g);
                if (std::fabs(next - g) < 1e-12) {
                    g = next;
                    break;
                }
                g = next;
            }
            return g;
        }

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

    namespace trygonometry
    {
        double normalize(double x) {
            // Normalize to range [-PI, PI]
            double two_pi = 2.0 * counterpp::trygonometry::PI;
            // Use fmod to reduce magnitude first
            x = std::fmod(x, two_pi);
            if (x > counterpp::trygonometry::PI) x -= two_pi;
            if (x < -counterpp::trygonometry::PI) x += two_pi;
            return x;
        }

        double sin(double val) {
            double x = normalize(val);
            double term = x;
            double out = x;
            for (int n = 1; n < 10; n++) {
                term *= -1.0 * x * x / ((2 * n) * (2 * n + 1));
                out += term;
            }
            return out;
        }

        double cos(double val) {
            double x = normalize(val);
            double term = 1.0;
            double out = 1.0;
            for (int n = 1; n < 10; n++) {
                term *= -1.0 * x * x / ((2 * n - 1) * (2 * n));
                out += term;
            }
            return out;
        }

        double tan(double val) {
            double x = normalize(val);
            double c = cos(x);
            if (std::fabs(c) < counterpp::trygonometry::EPSILON) {
                throw std::invalid_argument("Tangent undefined: cosine is zero (or too close to zero).");
            }
            return sin(x) / c;
        }

        int integrate(std::function<double(double)> f, double a, double b, int n) {
            if (n <= 0) {
                throw std::invalid_argument("Number of intervals must be positive.");
            }

            double h = (b - a) / n;
            double sum = 0.5 * (f(a) + f(b));

            for (int i = 1; i < n; i++) {
                double x = a + i * h;
                sum += f(x);
            }
            return static_cast<int>(sum * h); // Cast to int for return type
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
            return inline_asm::sqrt(variance(arr, size));
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
        constexpr int and_op(int a, int b) {
            return a & b;
        }
        constexpr int or_op(int a, int b) {
            return a | b;
        }
        constexpr int xor_op(int a, int b) {
            return a ^ b;
        }
        constexpr int not_op(int a) {
            return ~a;
        }
        constexpr int left_shift(int a, int n) {
            return a << n;
        }
        constexpr int right_shift(int a, int n) {
            return a >> n;
        }
    }
    namespace random
    {
       int rand_int(int min, int max) {
           srand(static_cast<unsigned>(time(0)));
            if (min > max) {
                throw std::invalid_argument("Min must be less than or equal to max.");
            }
            return min + rand() % (max - min + 1);
        }
        double rand_double(double min, double max) {
            srand(static_cast<unsigned>(time(0)));
            if (min >= max) {
                throw std::invalid_argument("Min must be less than max.");
            }
            return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
        }
        void seed(unsigned int seed) {
            srand(seed);
		}

        std::string randomKey(KeyType type, int length) {
            srand(static_cast<unsigned>(time(0)));

            if (length <= 0) {
                throw std::invalid_argument("Length must be positive.");
            }

            std::string characters;

            switch (type) {
            case KeyType::Letters:
                characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                break;
            case KeyType::Numbers:
                characters = "0123456789";
                break;
            case KeyType::Mixed:
                characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
                break;
            default:
                throw std::invalid_argument("Invalid KeyType.");
            }

            std::string key;
            for (int i = 0; i < length; i++) {
                key += characters[rand() % characters.length()];
            }

            return key;
        }
    }
}