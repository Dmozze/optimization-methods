#include <iostream>
#include "search-metods.h"
#include <functional>
#include <cmath>
#include <iomanip>

int main() {
    search_methods sm(1e-6);
    std::function<double(double)> func = [](double x) {
        return -5 * pow(x, 5) + 4 * pow(x, 4) - 12 * pow(x, 3) + 11 * pow(x, 2) - 2 * x + 1;
    };
    std::function<double(double)> func1 = [](double x) {
            return 0.2 * x * log10(x) + (x - 2.3) * (x - 2.3);
    };
    std::cout << std::setprecision(15);
    range r = {-0.5, 0.5};
    point_and_value dichotomy_answer = sm.dichotomy(func, r);
    std::cout << "dichotomy: " << dichotomy_answer.point << ' ' << dichotomy_answer.value << std::endl;
    point_and_value dichotomy_recursive_answer = sm.dichotomy_recursive(func, r);
    std::cout << "dichotomy_recursive: " << dichotomy_recursive_answer.point << ' ' << dichotomy_recursive_answer.value << std::endl;
    range r_fib = sm.fibonacci(func, r);
    std::cout << "fibonacci interval: " << r_fib.left <<  ' ' << r_fib.right << std::endl;
    point_and_value fib_answer{};
    fib_answer.point = r_fib.median();
    fib_answer.value = func(fib_answer.point);
    std::cout << "fibonacci: " << fib_answer.point << ' ' << fib_answer.value << std::endl;
    std::cout << fib_answer.value - dichotomy_answer.value;
    return 0;
}