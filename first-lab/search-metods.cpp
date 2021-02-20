#include "search-metods.h"


double search_methods::dichotomy(std::function<double(double)> &func, search_methods::range &r) {
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