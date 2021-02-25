#include "search-metods.h"
#include <cmath>
#include <iostream>

std::function<double(double)> search_methods::find_cnt_func(std::function<double(double)> &func, int &cnt) {
    cnt = 0;
    return [&cnt, &func] (double val) {
        cnt++;
        return func(val);
    };
}

information_search search_methods::dichotomy(std::function<double(double)> &func, range r) const {
    int cnt = 0;
    std::function<double(double)> func_cnt = find_cnt_func(func, cnt);
    double delta = epsilon / 2;
    while (r.delta() / 2 > epsilon) {
        double x1 = (r.right() + r.left() - delta) / 2;
        double x2 = (r.right() + r.left() + delta) / 2;
        if (func_cnt(x1) <= func_cnt(x2)) {
            r.update_range(r.left(), x2);
        } else {
            r.update_range(x1, r.right());
        }
    }
    information_search answer(r.median(), func_cnt(r.median()), cnt, r);
//    answer.point = (r.right() + r.left()) / 2;
//    answer.value = func_cnt(answer.point);
//    answer.times = cnt;
//    answer.r = r;
    return answer;
}

double search_methods::F(int n) {
    return std::ceil((pow((1 + sqrt(5)) / 2, n)) / sqrt(5));
}

information_search search_methods::fibonacci(std::function<double(double)> &func, range r) const {
    int cnt;
    std::function<double(double)> func_cnt = find_cnt_func(func, cnt);
    int n = std::ceil(log(sqrt(5) * (r.right() - r.left()) / epsilon) / log((1 + sqrt(5)) / 2));
    double x1 = r.left() + F(n - 2) / F(n) * (r.right() - r.left());
    double x2 = r.left() + F(n - 1) / F(n) * (r.right() - r.left());
    double f_x1 = func(x1);
    double f_x2 = func(x2);
    for (int k = 1; k < n - 1; k++) {
        if (f_x1 > f_x2) {
            r.update_range(x1, r.right());
            x1 = x2;
            f_x1 = f_x2;
            x2 = r.left() + 1. * F(n - k - 1) / F(n - k) * (r.right() - r.left());
            if (k != n - 2) {
                f_x2 = func_cnt(x2);
            }
        } else {
            r.update_range(r.left(), x2);
            x2 = x1;
            f_x2 = f_x1;
            x1 = r.left() + F(n - k - 2) / F(n - k) * (r.right() - r.left());
            if (k != n - 2) {
                f_x1 = func_cnt(x1);
            }
        }
    }
    x2 = x1 + epsilon;
    r.update_range(x1, x2);
    f_x2 = func_cnt(x2);
    information_search answer(x2, f_x2, cnt, r);
//    answer.point = x2;
//    answer.value = f_x2;
//    answer.times = cnt;
//    answer.r = &r;
    return answer;
}

//
//information_search search_methods::combined_brent(std::function<double(double)> &func, range r) {
//    double K = (3 - sqrt(5)) / 2;
//    double x, w, u;
//    double a = r.l;
//    double c = r.r;
//    x = w = u = a + K * (c - a);
//    double fx, fw, fu;
//    fx = fw = fu = func(x);
//    double d, e;
//    d = e = c - a;
//    while (true) {
//        double g = e;
//        e = d;
//        double tol = epsilon * std::abs(x) + epsilon / 10;
//        if (std::abs(x - (a + c) / 2) + (c - a) / 2 <= 2 * tol) {
//            break;
//        }
//
//    }
//
//    return {0.,0.};
//}



//void search_methods::init_fibonacci(double uncertainty) {
//    F.reserve(10);
//    F.push_back(1);
//    F.push_back(1);
//    while (F.back() <= static_cast<int>(uncertainty)) {
//        F.push_back(F.back() + F[F.size() - 2]);
//    }
//}
//
//range search_methods::fibonacci(std::function<double(double)> &func, range r) {
//    init_fibonacci(r.delta() / epsilon);
//    int n = F.size() - 1;
//    double a = r.l;
//    double b = r.r;
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

