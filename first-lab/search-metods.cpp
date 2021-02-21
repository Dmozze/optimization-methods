#include "search-metods.h"
#include <cmath>
#include <iostream>

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
    range new_r{};
    if (func(x1) <= func(x2)) {
        new_r = {r.left, x2};
    } else {
        new_r = {x1, r.right};
    }
    return dichotomy_recursive(func, new_r);
}

//void search_methods::init_fibonacci(double uncertainty) {
//    F.reserve(10);
//    F.push_back(1);
//    F.push_back(1);
//    while (F.back() <= static_cast<int>(uncertainty)) {
//        F.push_back(F.back() + F[F.size() - 2]);
//    }
//}

double search_methods::F(int n) {
    return std::ceil((pow((1 + sqrt(5)) / 2, n)) / sqrt(5));
}


range search_methods::fibonacci(std::function<double(double)> &func, range &r) {
    double a = r.left;
    double b = r.right;
    int n = std::ceil(log(sqrt(5) * (b - a) / epsilon)/log((1+sqrt(5)) / 2));
    double lambda = a + F(n - 2) / F(n) * (b - a);
    double mu = a + F(n - 1) / F(n) * (b - a);
    double f_lambda = func(lambda);
    double f_mu = func(mu);
    for (int k = 1; k < n - 1; k++) {
        if (f_lambda > f_mu) {
            a = lambda;
            lambda = mu;
            f_lambda = f_mu;
            mu = a + 1. * F(n - k - 1) / F(n - k) * (b - a);
            if (k != n - 2) {
                f_mu = func(mu);
            }
        } else {
            b = mu;
            mu = lambda;
            f_mu = f_lambda;
            lambda = a + F(n - k - 2) / F(n - k) * (b - a);
            if (k != n - 2) {
                f_lambda = func(lambda);
            }
        }
    }
    mu = lambda + epsilon;
    f_mu = func(mu);
    f_lambda = func(lambda);
    if (f_mu == f_lambda) {
        a = lambda;
    } else {
        b = mu;
    }

    return range{a, b};
}
//
//range search_methods::fibonacci(std::function<double(double)> &func, range &r) {
//    init_fibonacci(r.delta() / epsilon);
//    int n = F.size() - 1;
//    double a = r.left;
//    double b = r.right;
//    double lambda = a + 1. * F[n - 2] / F[n] * (b - a);
//    double mu = a + 1. * F[n - 1] / F[n] * (b - a);
//    double f_lambda = func(lambda);
//    double f_mu = func(mu);
//    for (int k = 1; k < n - 1; k++) {
//        if (f_lambda > f_mu) {
//            a = lambda;
//            lambda = mu;
//            f_lambda = f_mu;
//            mu = a + 1. * F[n - k - 1] / F[n - k] * (b - a);
//            if (k != n - 2) {
//                f_mu = func(mu);
//            }
//        } else {
//            b = mu;
//            mu = lambda;
//            f_mu = f_lambda;
//            lambda = a + F[n - k - 2] / F[n - k] * (b - a);
//            if (k != n - 2) {
//                f_lambda = func(lambda);
//            }
//        }
//    }
//    mu = lambda + epsilon;
//    f_mu = func(mu);
//    f_lambda = func(lambda);
//    if (f_mu == f_lambda) {
//        a = lambda;
//    } else {
//        b = mu;
//    }
//
//    return range{a, b};
//}

