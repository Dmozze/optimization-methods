#pragma once
#include <functional>
#include <vector>
#include <fstream>
#include <iostream>

class range {
    std::vector<std::pair<double, double>> range_history;
public:

    range(double l, double r) : range_history() {
        range_history.emplace_back(l, r);
    }
    double delta() const {
        return right() - left();
    }
    double median() const {
        return (right() + left()) / 2;
    }
    double right() const {
        return range_history.back().second;
    }
    double left() const {
        return range_history.back().first;
    }
    void update_range(double l, double r) {
        std::cout << l << ' ' << r << std::endl;
        range_history.emplace_back(l, r);
    }
    void print(std::ofstream &out) {

        for (auto [left, right] : range_history) {
            out << left << ';' << right << std::endl;
        }
    }
};

struct information_search {
    double point;
    double value;
    int times;
    range r;
    information_search(double point, double value, int times, range &r)
    :
    point(point),
    value(value),
    times(times),
    r(r) {}
};

class search_methods {
    double epsilon;

    static double F(int n);

    static std::function<double(double)> find_cnt_func(std::function<double(double)> &func, int &cnt);
public:

    explicit search_methods(double epsilon) : epsilon(epsilon) {
    }

    information_search dichotomy(std::function<double(double)> &func, range r) const;

    information_search dichotomy_recursive(std::function<double(double)> &func, range r);

    information_search golden_ratio(std::function<double(double)> &func, range r);

    information_search fibonacci(std::function<double(double)> &func, range r) const;

    information_search parabolas(std::function<double(double)> &func, range r);

    information_search combined_brent(std::function<double(double)> &func, range r);


};