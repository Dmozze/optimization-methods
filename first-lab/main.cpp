#include <iostream>
#include "search-metods.h"
#include <functional>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>

void print(const std::string& s, information_search &inf, std::function<long double(long double)> &func) {
    std::ofstream out(s);
    out << std::setprecision(11);
    inf.r.print(out, func);
    out.flush();
    out.close();
}

const std::string fib = "fibonacci";
const std::string dich = "dichotomy";
const std::string gold = "golden";
const std::string parab = "parabola";
const std::string brent = "brent";
const std::string csv = ".csv";
const std::string path = "tex/tables/";

void print_cnt(const std::string& s, const std::vector<std::pair<long double, int>>& vec) {
    std::ofstream out(path + s + csv);
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
    //break
    std::function<long double(long double)> func2 = [](long double x) {
        return 1.68955 * powl(x, 4) - 10.4033 * powl(x, 3) + 19.3156 * powl(x, 2) - 9.26816 * x;
    };
    std::cout << std::setprecision(15);
    range r = {-0.5L, 0.5L};
    //range r = {0.5L, 2.5L};
    //range r = {0, 3};//break
    std::string brek = "";
    std::vector<std::pair<long double, int>> dichotomy;
    std::vector<std::pair<long double, int>> fibonacci;
    std::vector<std::pair<long double, int>> golden;
    std::vector<std::pair<long double, int>> parab_vec;
    std::vector<std::pair<long double, int>> brent_vec;
    for (long double epsilon = 1e-1L; epsilon > 1e-11L; epsilon *= 1e-1L) {
        long double log_epsilon = -log10l(epsilon);
        std::cout << epsilon <<  ' ' << log_epsilon << '\n';
        search_methods sm(epsilon);
        information_search dichotomy_answer = sm.dichotomy(func, r);
        std::cout << "dichotomy: " << dichotomy_answer.point << ' ' << dichotomy_answer.value << ' ' << dichotomy_answer.times << std::endl;
        information_search fib_answer = sm.fibonacci(func, r);
        std::cout << "fibonacci: " << fib_answer.point << ' ' << fib_answer.value << ' ' << fib_answer.times << std::endl;
        information_search golden_answer = sm.golden_ratio(func, r);
        std::cout << "golden: " << golden_answer.point << ' ' << golden_answer.value << ' ' << golden_answer.times << std::endl;
        information_search parabolas = sm.parabolas(func, r);
        std::cout << "parabolas: " << parabolas.point << ' ' << parabolas.value << ' ' << parabolas.times << std::endl;
        information_search brent_answer = sm.combined_brent(func, r);
        std::cout << "brent: " << brent_answer.point << ' ' << brent_answer.value << ' ' << brent_answer.times << std::endl;
        std::cout << parabolas.value - dichotomy_answer.value << std::endl;
        std::cout << fib_answer.value - dichotomy_answer.value << std::endl;
        std::cout << golden_answer.value - dichotomy_answer.value << std::endl;
        std::cout << brent_answer.value - dichotomy_answer.value << std::endl;
        std::cout << dichotomy_answer.times - fib_answer.times << std::endl;
        std::cout << dichotomy_answer.times - golden_answer.times << std::endl;
        std::cout << "\n*************\n\n";
        dichotomy.emplace_back(log_epsilon, dichotomy_answer.times);
        fibonacci.emplace_back(log_epsilon, fib_answer.times);
        golden.emplace_back(log_epsilon, golden_answer.times);
        parab_vec.emplace_back(log_epsilon, parabolas.times);
        brent_vec.emplace_back(log_epsilon, brent_answer.times);
        std::ostringstream s;
        s << std::setprecision(15) << epsilon;
        print(path + dich + brek + s.str() + csv, dichotomy_answer, func);
        print(path + fib + brek + s.str() + csv, fib_answer, func);
        print(path + gold + brek + s.str() + csv, golden_answer, func);
        print(path + parab + brek + s.str() + csv, parabolas, func);
        print(path + brent + brek + s.str() + csv, brent_answer, func);
    }

    print_cnt(dich + brek, dichotomy);
    print_cnt(fib + brek, fibonacci);
    print_cnt(gold + brek, golden);
    print_cnt(parab + brek, parab_vec);
    print_cnt(brent + brek, brent_vec);
    return 0;
}