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

information_search search_methods::dichotomy(std::function<double(double)> &func, range r) {
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
    return answer;
}

information_search search_methods::golden_ratio(std::function<double(double)> &func, range r) {
    int cnt;
    std::function<double(double)> func_cnt = find_cnt_func(func, cnt);
    double x1 = r.right() - golden_const * r.delta();
    double x2 = r.left() + golden_const * r.delta();
    double f_x1 = func_cnt(x1);
    double f_x2 = func_cnt(x2);
    while (true) {
        if (f_x1 > f_x2) {
            r.update_range(x1, r.right());
            x1 = x2;
            f_x1 = f_x2;
            x2 = r.left() + golden_const * r.delta();
            f_x2 = func_cnt(x2);
        } else {
            r.update_range(r.left(), x2);
            x2 = x1;
            f_x2 = f_x1;
            x1 = r.right() - golden_const * r.delta();
            f_x1 = func_cnt(x1);
        }
        if (r.delta() < epsilon) {
            break;
        }
    }
    double f_min, x_min;
    if (f_x1 < f_x2) {
        f_min = f_x1;
        x_min = r.left();
    } else {
        f_min = f_x2;
        x_min = r.right();
    }
    information_search answer(x_min, f_min, cnt, r);
    return answer;



}






double search_methods::F(int n) {
    return f[n - 1];
    //return std::ceil((pow((1 + sqrt(5)) / 2, n)) / sqrt(5));
}

information_search search_methods::fibonacci(std::function<double(double)> &func, range r) {
    int cnt;
    std::function<double(double)> func_cnt = find_cnt_func(func, cnt);
    int n = std::ceil(log(sqrt(5) * (r.right() - r.left()) / epsilon) / log((1 + sqrt(5)) / 2));
    double x1 = r.left() + F(n - 2) / F(n) * r.delta();
    double x2 = r.left() + F(n - 1) / F(n) * r.delta();
    double f_x1 = func(x1);
    double f_x2 = func(x2);
    for (int k = 1; k < n - 1; k++) {
        if (f_x1 > f_x2) {
            r.update_range(x1, r.right());
            x1 = x2;
            f_x1 = f_x2;
            x2 = r.left() + F(n - k - 1) / F(n - k) * r.delta();
            if (k != n - 2) {
                f_x2 = func_cnt(x2);
            }
        } else {
            r.update_range(r.left(), x2);
            x2 = x1;
            f_x2 = f_x1;
            if (k != n - 2) {
                x1 = r.left() + F(n - k - 2) / F(n - k) * r.delta();
                f_x1 = func_cnt(x1);
            }
        }
    }
    x2 = x1 + epsilon;
    r.update_range(x1, x2);
    f_x2 = func_cnt(x2);
    information_search answer(x2, f_x2, cnt, r);
    return answer;
}

//information_search search_methods::combined_brent(std::function<double(double)> &func, range r) {
//    int cnt;
//    std::function<double(double)> func_cnt = find_cnt_func(func, cnt);
//
//}
