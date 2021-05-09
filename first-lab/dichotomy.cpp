#include "search-metods.h"

information_search search_methods::dichotomy(std::function<long double(long double)>& func, range r) const {
    size_t cnt = 0;
    std::function<long double(long double)> func_cnt = find_cnt_func(func, cnt);
    long double delta = epsilon / 2;
    while (r.delta() / 2 > epsilon) {
        long double x1 = (r.right() + r.left() - delta) / 2;
        long double x2 = (r.right() + r.left() + delta) / 2;
        if (func_cnt(x1) <= func_cnt(x2)) {
            r.update_range(r.left(), x2);
        } else {
            r.update_range(x1, r.right());
        }
    }
    information_search answer(r.median(), func_cnt(r.median()), cnt, r);
    return answer;
}
