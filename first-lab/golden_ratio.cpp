#include "search-metods.h"

information_search search_methods::golden_ratio(std::function<long double(long double)> &func, range r) const {
    int cnt;
    std::function<long double(long double)> func_cnt = find_cnt_func(func, cnt);
    long double x1 = r.right() - golden_const * r.delta();
    long double x2 = r.left() + golden_const * r.delta();
    long double f_x1 = func_cnt(x1);
    long double f_x2 = func_cnt(x2);
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
    long double f_min, x_min;
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
