#include "search-metods.h"

information_search search_methods::fibonacci(std::function<long double(long double)> &func, range r) {
    int cnt;
    std::function<long double(long double)> func_cnt = find_cnt_func(func, cnt);
    int n = ceill(log(sqrtl(5) * (r.right() - r.left()) / epsilon) / logl((1 + sqrtl(5)) / 2));
    long double x1 = r.left() + F(n - 2) / F(n) * r.delta();
    long double x2 = r.left() + F(n - 1) / F(n) * r.delta();
    long double f_x1 = func(x1);
    long double f_x2 = func(x2);
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

