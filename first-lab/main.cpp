#include <iostream>
#include "search-metods.h"
#include <functional>
#include <cmath>
#include <iomanip>

int main() {
    search_methods sm(1e-5);
    std::function<double(double)> func = [](double x) {
        return -5 * pow(x, 5) + 4 * pow(x, 4) - 12 * pow(x, 3) + 11 * pow(x, 2) - 2 * x + 1;
    };
    std::cout << std::setprecision(15);
    range r = {-0.5, 0.5};
    std::cout << "dichotomy: " << sm.dichotomy(func, r) << std::endl;
    std::cout << "dichotomy_recursive: " << sm.dichotomy_recursive(func, r) << std::endl;
    range r_fib = sm.fibonacci(func, r);
    double fib_ans = (func(r_fib.left) + func(r_fib.right)) / 2;
    std::cout << "fibonacci: " << fib_ans << std::endl;
    std::cout << fib_ans - sm.dichotomy(func, r);
    return 0;
}