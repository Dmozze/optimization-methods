#pragma once
#include <functional>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

class range {
    std::vector<std::pair<long double, long double>> range_history;

public:
    range(long double l, long double r)
        : range_history() {
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
    void print(std::ofstream& out, std::function<long double(long double)>& func) {
        out << "iter;left;right;ratio;f(left);f(right)" << std::endl;
        for (size_t i = 0; i < range_history.size(); i++) {
            out << i + 1 << ';';
            const long double l = range_history[i].first;
            const long double r = range_history[i].second;
            out << l << ';' << r << ';';
            if (i > 0) {
                const long double l_ = range_history[i - 1].first;
                const long double r_ = range_history[i - 1].second;
                out << (r_ - l_) / (r - l);
            }
            out << ';' << func(l) << ';' << func(r) << std::endl;
        }
    }
    void print(std::ostream& out, std::function<long double(long double)>& func) {
        out << "iter;left;right;ratio;f(left);f(right)" << std::endl;
        for (size_t i = 0; i < range_history.size(); i++) {
            out << i + 1 << ';';
            const long double l = range_history[i].first;
            const long double r = range_history[i].second;
            out << l << ';' << r << ';';
            if (i > 0) {
                const long double l_ = range_history[i - 1].first;
                const long double r_ = range_history[i - 1].second;
                out << (r_ - l_) / (r - l);
            }
            out << ';' << func(l) << ';' << func(r) << std::endl;
        }
    }
};

struct information_search {
    long double point;
    long double value;
    int times;
    range r;
    information_search(long double point, long double value, int times, range& r)
        : point(point)
        , value(value)
        , times(times)
        , r(r) {
    }
};

class search_methods {
    static constexpr size_t number_fib = 90;
    const long double golden_const = 0.5 * (sqrtl(5) - 1);

    long double epsilon;
    std::vector<long double> f;

    long double F(size_t n);

    static long double calc_u(const long double& x1, const long double& f_x1,
                              const long double& x2, const long double& f_x2,
                              const long double& x3, const long double& f_x3);

    information_search research_parabolas_(std::function<long double(long double)>& func, range r, long double& current_mid, long double step) const;

public:
    explicit search_methods(long double epsilon)
        : epsilon(epsilon)
        , f() {
        f.push_back(1.);
        f.push_back(1.);
        for (size_t i = 0; i < number_fib; i++) {
            f.push_back(f.back() + f[f.size() - 2]);
        }
    }

    information_search dichotomy(std::function<long double(long double)>& func, range r) const;

    information_search golden_ratio(std::function<long double(long double)>& func, range r) const;

    information_search fibonacci(std::function<long double(long double)>& func, range r);

    information_search parabolas(std::function<long double(long double)>& func, range r) const;

    void research_parabolas(std::function<long double(long double)>& func, range r, long double step) const;

    information_search combined_brent(std::function<long double(long double)>& func, range r) const;

    static std::function<long double(long double)>
    find_cnt_func(std::function<long double(long double)>& func, size_t& cnt);
};