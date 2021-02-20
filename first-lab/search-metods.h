#pragma once
#include <functional>


struct range {
    double left;
    double right;
    double delta() {
        return right - left;
    }
    double median() {
        return (right + left) / 2;
    }
};

class search_methods {
    double epsilon;


public:

    search_methods(double epsilon) : epsilon(epsilon) {
    }

    double dichotomy(std::function<double(double)> &func, range &r);

    double dichotomy_recursive(std::function<double(double)> &func, range &r);

    double golden_ratio(std::function<double(double)> &func, range &r);

    double fibonacci(std::function<double(double)> &func, range &r);

    double parabolas(std::function<double(double)> &func, range &r);

    double brenta(std::function<double(double)> &func, range &r);


};