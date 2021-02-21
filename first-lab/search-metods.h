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
};

class search_methods {
    double epsilon;
//    std::vector<int> F;

    void init_fibonacci(double uncertainty);

    double F(int n);
public:

    search_methods(double epsilon) : epsilon(epsilon) {
    }

    point_and_value dichotomy(std::function<double(double)> &func, range &r);

    point_and_value dichotomy_recursive(std::function<double(double)> &func, range &r);

    point_and_value golden_ratio(std::function<double(double)> &func, range &r);

    range fibonacci(std::function<double(double)> &func, range &r);

    point_and_value parabolas(std::function<double(double)> &func, range &r);

    point_and_value combined_brent(std::function<double(double)> &func, range &r);


};