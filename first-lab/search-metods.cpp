#include "search-metods.h"

std::function<long double(long double)>
search_methods::find_cnt_func(std::function<long double(long double)> &func, int &cnt) {
    cnt = 0;
    return [&cnt, &func] (long double val) {
        cnt++;
        return func(val);
    };
}

long double search_methods::F(int n) {
    return f[n - 1];
    //return ceill((pow((1 + sqrt(5)) / 2, n)) / sqrt(5));
}

