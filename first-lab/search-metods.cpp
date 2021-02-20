#include "search-metods.h"


double search_methods::dichotomy(std::function<double(double)> &func, range &r) {
    double right = r.right;
    double left = r.left;
    double delta = epsilon / 2;
    while ((right - left) / 2 > epsilon) {
        double x1 = (right + left - delta) / 2;
        double x2 = (right + left + delta) / 2;
        if (func(x1) <= func(x2)) {
            right = x2;
        } else {
            left = x1;
        }
    }
    return func((right + left) / 2);
}

double search_methods::dichotomy_recursive(std::function<double(double)> &func, range &r) {
    if (r.delta() / 2 <= epsilon) {
        return func(r.median());
    }
    double x1 = (r.right + r.left - epsilon / 2) / 2;
    double x2 = (r.right + r.left + epsilon / 2) / 2;
    range new_r;
    if (func(x1) <= func(x2)) {
        new_r = {r.left, x2};
    } else {
        new_r = {x1, r.right};
    }
    return dichotomy_recursive(func, new_r);
}

double search_methods::fibonacci(std::function<double(double)> &func, range &r) {
    return 0.;
}

