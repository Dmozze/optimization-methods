#pragma once
#include <functional>
#include <vector>


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
    std::vector<int> F;

    void init_fibonacci(double uncertainty);

public:

    search_methods(double epsilon) : epsilon(epsilon) {
    }

    double dichotomy(std::function<double(double)> &func, range &r);

    double dichotomy_recursive(std::function<double(double)> &func, range &r);

    double golden_ratio(std::function<double(double)> &func, range &r);

    range fibonacci(std::function<double(double)> &func, range &r);

    double parabolas(std::function<double(double)> &func, range &r);

    double brenta(std::function<double(double)> &func, range &r);


};