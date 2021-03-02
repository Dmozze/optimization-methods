#include <iostream>
#include "search-metods.h"
#include <functional>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>

void print(std::string s, information_search &inf) {
    std::ofstream out(s);
    out << std::setprecision(15);
    out << "left;right" << std::endl;
    inf.r.print(out);
    out.flush();
    out.close();
}

void print_cnt(std::string s, std::vector<std::pair<double, int>> vec) {
    std::ofstream out("tables/" + s + ".csv");
    out << std::setprecision(15);
    out << "log;cnt" << std::endl;
    for (auto [log_eps, cnt] : vec) {
        out << log_eps << ';' << cnt << std::endl;
    }
    out.flush();
    out.close();
}


int main() {
    std::function<long double(long double)> func = [](long double x) {
        return -5 * powl(x, 5) + 4 * powl(x, 4) - 12 * powl(x, 3) + 11 * powl(x, 2) - 2 * x + 1;
    };
    std::function<long double(long double)> func1 = [](long double x) {
        return 0.2L * x * log10l(x) + (x - 2.3L) * (x - 2.3L);
    };
    std::cout << std::setprecision(15);
    range r = {-0.5L, 0.5L};
    std::vector<std::pair<double, int>> dichotomy;
    std::vector<std::pair<double, int>> fibonacci;
    std::vector<std::pair<double, int>> golden;
    std::string fib = "fibonacci";
    std::string dich = "dichotomy";
    std::string gold = "golden";
    std::string csv = ".csv";
    for (long double epsilon = 1e-1L; epsilon > 1e-11L; epsilon *= 1e-1L) {
        std::cout << epsilon <<  ' ' << -log10l(epsilon) << '\n';
        search_methods sm(epsilon);
        information_search dichotomy_answer = sm.dichotomy(func, r);
        std::cout << "dichotomy: " << dichotomy_answer.point << ' ' << dichotomy_answer.value << ' ' << dichotomy_answer.times << std::endl;
        information_search fib_answer = sm.fibonacci(func, r);
        std::cout << "fibonacci: " << fib_answer.point << ' ' << fib_answer.value << ' ' << fib_answer.times << std::endl;
        information_search golden_answer = sm.golden_ratio(func, r);
        std::cout << "golden: " << golden_answer.point << ' ' << golden_answer.value << ' ' << golden_answer.times << std::endl;
        std::cout << fib_answer.value - dichotomy_answer.value << std::endl;
        std::cout << golden_answer.value - dichotomy_answer.value << std::endl;
        std::cout << dichotomy_answer.times - fib_answer.times << std::endl;
        std::cout << dichotomy_answer.times - golden_answer.times << std::endl;
        std::cout << "\n*************\n\n";
        dichotomy.emplace_back(-log10l(epsilon), dichotomy_answer.times);
        fibonacci.emplace_back(-log10l(epsilon), fib_answer.times);
        golden.emplace_back(-log10l(epsilon), golden_answer.times);
        std::ostringstream s;
        s << std::setprecision(15) << epsilon;
        print("tables/" + dich + s.str() + csv, fib_answer);
        print("tables/" + fib + s.str() + csv, dichotomy_answer);
        print("tables/" + gold + s.str() + csv, golden_answer);
    }

    print_cnt(dich, dichotomy);
    print_cnt(fib, fibonacci);
    print_cnt(gold, golden);
    return 0;
}