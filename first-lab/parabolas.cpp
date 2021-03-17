#include "search-metods.h"
#include <random>

std::pair<long double, long double>
find_mid(const std::function<long double(long double)> &func, const range &r, const long double &f_x1,
         const long double &f_x2) {
    long double mid = 0, f_mid = 0;
    long double left = r.left(), right = r.right();
    while (true) {
        mid = left + (right - left) / 2;
        f_mid = func(mid);
        if (f_mid < f_x2 && f_mid < f_x1) {
            break;
        }
        if (f_mid >= f_x1){
            left = mid;
        }
        if (f_mid >= f_x2) {
            right = mid;
        }
    }
    return {mid, f_mid};
}

long double search_methods::calc_u(const long double &x1, const long double &f_x1,
                   const long double &x2, const long double &f_x2,
                   const long double &x3, const long double &f_x3) {
    const long double delta_x2_x1 = (x2 - x1);
    const long double delta_f2_f3 = (f_x2 - f_x3);
    const long double delta_x2_x3 = (x2 - x3);
    const long double delta_f2_f1 = (f_x2 - f_x1);
    return x2 - (delta_x2_x1 * delta_x2_x1 * delta_f2_f3 - delta_x2_x3 * delta_x2_x3 * delta_f2_f1) /
                (2 * (delta_x2_x1 * delta_f2_f3 - delta_x2_x3 * delta_f2_f1));
}

information_search search_methods::parabolas(std::function<long double(long double)> &func, range r) const {
    size_t cnt = 0;
    const std::function<long double(long double)> func_cnt = find_cnt_func(func, cnt);
    long double x1 = r.left();
    long double x3 = r.right();
    long double f_x1 = func_cnt(x1);
    long double f_x3 = func_cnt(x3);
    long double x_min = 0, f_min = 0;
    auto [x2, f_x2] = find_mid(func_cnt, r, f_x1, f_x3);
    while (true) {
        long double u = calc_u(x1, f_x1, x2, f_x2, x3, f_x3);
        long double f_u = func_cnt(u);
        if (std::abs(u - x2) < epsilon){
            x_min = u;
            f_min = f_u;
            break;
        }
        if (u < x2) {
            if (f_u < f_x2) {
                x3 = x2;
                x2 = u;
                f_x3 = f_x2;
                f_x2 = func_cnt(x2);
            } else {
                x1 = u;
                f_x1 = func_cnt(x1);
            }
        } else {
            if (f_x2 < f_u) {
                x3 = u;
                f_x3 = func_cnt(x3);
            } else {
                x1 = x2;
                x2 = u;
                f_x1 = f_x2;
                f_x2 = func_cnt(x2);
            }
        }
        r.update_range(x1, x3);
    }
    information_search answer(x_min, f_min, cnt, r);
    return answer;
}
