#include "search-metods.h"
#include <random>
#include <iomanip>

std::pair<long double, long double>
research_find_mid(const std::function<long double(long double)>& func, const range& r, const long double& f_x1,
                  const long double& f_x2, long double& mid, const long double step) {
    mid += step;
    long double f_mid = func(mid);
    while (mid < r.right() && !(f_mid < f_x2 && f_mid < f_x1)) {
        mid += step;
        f_mid = func(mid);
    }
    if (mid > r.right()) {
        return {0.0, 0.0};
    }
    return {mid, f_mid};
}

information_search search_methods::research_parabolas_(std::function<long double(long double)>& func, range r, long double& current_mid, long double step) const {
    size_t cnt = 0;
    const std::function<long double(long double)> func_cnt = search_methods::find_cnt_func(func, cnt);
    long double x1 = r.left();
    long double x3 = r.right();
    long double f_x1 = func_cnt(x1);
    long double f_x3 = func_cnt(x3);
    long double x_min = 0, f_min = 0;
    auto [x2, f_x2] = research_find_mid(func, r, f_x1, f_x3, current_mid, step);
    cnt++; // only for research         _/\_
    if (x2 == 0.0 && f_x2 == 0.0) {
        information_search answer(0.0, 0.0, -1, r);
        return answer;
    }
    while (true) {
        long double u = calc_u(x1, f_x1, x2, f_x2, x3, f_x3);
        long double f_u = func_cnt(u);
        if (std::abs(u - x2) < epsilon) {
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

void search_methods::research_parabolas(std::function<long double(long double)>& func, range r,
                                        long double step) const {
    std::ostringstream s;
    s << std::setprecision(15) << epsilon;
    std::ofstream out("tex/tables/research_parabolas" + s.str() + ".csv");
    out << std::setprecision(15);
    out << "point;cnt" << std::endl;
    long double current_mid = r.left();
    while (true) {
        information_search inf = research_parabolas_(func, r, current_mid, step);
        if (inf.times == -1) {
            break;
        }
        out << current_mid << ';' << inf.times << std::endl;
    }
    out.close();
}
