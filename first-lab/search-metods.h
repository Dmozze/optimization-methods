#pragma once
#include <functional>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

class range {
    std::vector<std::pair<double, double>> range_history;
public:

    range(long double l, long double r) : range_history() {
        range_history.emplace_back(l, r);
    }
    long double delta() const {
        return right() - left();
    }
    long double median() const {
        return (right() + left()) / 2;
    }
    long double right() const {
        return range_history.back().second;
    }
    long double left() const {
        return range_history.back().first;
    }
    void update_range(long double l, long double r) {
        range_history.emplace_back(l, r);
    }
    void print(std::ofstream &out) {

        for (auto [left, right] : range_history) {
            out << left << ';' << right << std::endl;
        }
    }
};

struct information_search {
    long double point;
    long double value;
    int times;
    range r;
    information_search(long double point, long double value, int times, range &r)
    :
    point(point),
    value(value),
    times(times),
    r(r) {}
};

class search_methods {
    std::vector<long double> f;
    const size_t number_fib = 90;

    long double epsilon;

    const long double golden_const = 0.5 * (sqrtl(5) - 1);

    long double F(size_t n);



    static std::function<long double(long double)>
    find_cnt_func(std::function<long double(long double)> &func, size_t &cnt);
public:

    explicit search_methods(long double epsilon) : epsilon(epsilon), f() {
        f.push_back(1.);
        f.push_back(1.);
        for (int i = 0; i < number_fib; i++) {
            f.push_back(f.back() + f[f.size() - 2]);
        }
    }

    information_search dichotomy(std::function<long double(long double)> &func, range r) const;

    information_search golden_ratio(std::function<long double(long double)> &func, range r) const;

    information_search fibonacci(std::function<long double(long double)> &func, range r);

    information_search parabolas(std::function<long double(long double)> &func, range r) const;

    information_search combined_brent(std::function<long double(long double)> &func, range r) const;


};