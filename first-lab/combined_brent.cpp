#include "search-metods.h"

template <typename T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

information_search search_methods::combined_brent(std::function<long double(long double)>const& func, range r) const {
    size_t cnt = 0;
    const std::function<long double(long double)> func_cnt = find_cnt_func(func, cnt);
    long double a = r.left(), c = r.right();
    long double x = a + golden_const * r.delta();
    long double f_x = func_cnt(x);
    long double w = x, v = x;
    long double f_w = f_x, f_v = f_x;
    long double d = r.delta(), e = r.delta();
    long double x_min = 0, f_min = 0;
    while (true) {
        long double g = e;
        e = d;
        long double tol = epsilon * std::abs(x) + epsilon / 10;
        long double u;
        bool normal_parabola = false;
        if (std::abs(x - (a + c) / 2) + r.delta() / 2 <= 2 * tol) {
            x_min = x;
            f_min = f_x;
            break;
        }
        if (x != w && w != v && v != x && f_x != f_w && f_w != f_v && f_v != f_x) {
            u = calc_u(x, f_x, w, f_w, v, f_v);
            if (a <= u && u <= c && std::abs(u - x) < g / 2) {
                normal_parabola = true;
                if (u - a < 2 * tol || c - u < 2 * tol) {
                    u = x - sign(x - (a + c) / 2) * tol;
                }
            }
        }
        if (!normal_parabola) {
            if (x < (a + c) / 2) {
                u = x + golden_const * (c - x);
                e = c - x;
            } else {
                u = x - golden_const * (x - a);
                e = x - a;
            }
        }
        if (std::abs(u - x) < tol) {
            u = x + sign(u - x) * tol;
        }
        d = std::abs(u - x);
        long double f_u = func_cnt(u);
        if (f_u <= f_x) {
            if (u >= x) {
                a = x;
            } else {
                c = x;
            }
            v = w;
            f_v = f_w;
            w = x;
            f_w = f_x;
            x = u;
            f_x = f_u;
        } else {
            if (u >= x) {
                c = u;
            } else {
                a = u;
            }
            if (f_u <= f_w || w == x) {
                v = w;
                f_v = f_w;
                w = u;
                f_w = f_u;
            } else {
                if (f_u <= f_v || v == x || v == w) {
                    v = u;
                    f_v = f_u;
                }
            }
        }
        r.update_range(a, c);
    }
    information_search answer(x_min, f_min, cnt, r);
    return answer;
}
