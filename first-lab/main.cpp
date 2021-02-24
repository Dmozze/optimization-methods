#include <iostream>
#include "search-metods.h"
#include <functional>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>

int main() {
    std::function<double(double)> func = [](double x) {
        return -5 * pow(x, 5) + 4 * pow(x, 4) - 12 * pow(x, 3) + 11 * pow(x, 2) - 2 * x + 1;
    };
    std::function<double(double)> func1 = [](double x) {
        return 0.2 * x * log10(x) + (x - 2.3) * (x - 2.3);
    };
    std::cout << std::setprecision(15);
    range r = {-0.5, 0.5};
    std::vector<std::pair<double, int>> dichotomy;
    std::vector<std::pair<double, int>> fibonacci;
    for (double epsilon = 1e-1; epsilon > 1e-11; epsilon *= 0.9) {
        std::cout << epsilon <<  ' ' << -log10(epsilon) << '\n';
        search_methods sm(epsilon);
        point_and_value dichotomy_answer = sm.dichotomy(func, r);
        std::cout << "dichotomy: " << dichotomy_answer.point << ' ' << dichotomy_answer.value << ' ' << dichotomy_answer.times << std::endl;
        point_and_value dichotomy_recursive_answer = sm.dichotomy_recursive(func, r);
        std::cout << "dichotomy_recursive: " << dichotomy_recursive_answer.point << ' ' << dichotomy_recursive_answer.value << std::endl;
        point_and_value fib_answer = sm.fibonacci(func, r);
        std::cout << "fibonacci: " << fib_answer.point << ' ' << fib_answer.value << ' ' << fib_answer.times << std::endl;
        std::cout << fib_answer.value - dichotomy_answer.value << std::endl;
        std::cout << dichotomy_answer.times - fib_answer.times;
        std::cout << "\n*************\n\n";
        dichotomy.emplace_back(-log10(epsilon), dichotomy_answer.times);
        fibonacci.emplace_back(-log10(epsilon), fib_answer.times);
    }

    std::ofstream dichotomy_stream("tables/dichotomy.csv");
    std::ofstream fibonacci_stream("tables/fibonacci.csv");
    for (auto [log_eps, cnt] : dichotomy) {
        dichotomy_stream << log_eps << ';' << cnt << std::endl;
    }
    for (auto [log_eps, cnt] : fibonacci) {
        fibonacci_stream << log_eps << ';' << cnt << std::endl;
    }

    return 0;
}