#pragma once
#include <functional>
#include <vector>


struct range {
    double left;
    double right;
    double delta() const {
        return right - left;
    }
    double median() const {
        return (right + left) / 2;
    }
};

struct point_and_value {
    double point;
    double value;
    double times;
};

class search_methods {
    double epsilon;

    static double F(int n);

    static std::function<double(double)> find_cnt_func(std::function<double(double)> &func, int &cnt);
public:

    explicit search_methods(double epsilon) : epsilon(epsilon) {
    }

    point_and_value dichotomy(std::function<double(double)> &func, range &r) const;

    point_and_value dichotomy_recursive(std::function<double(double)> &func, range &r);

    point_and_value golden_ratio(std::function<double(double)> &func, range &r);

    point_and_value fibonacci(std::function<double(double)> &func, range &r) const;

    point_and_value parabolas(std::function<double(double)> &func, range &r);

    point_and_value combined_brent(std::function<double(double)> &func, range &r);


};