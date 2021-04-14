#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <algorithm>
#include "GeneratorQuadraticFunction.h"


std::vector<GeneratorQuadraticFunction::T> GeneratorQuadraticFunction::gen_quad(size_t n, T k) {
    T lower_bound = 1;
    T upper_bound = k;
    std::uniform_real_distribution<T> unif(lower_bound,upper_bound);
    T t = 1; /*unif(generator);*/
    T t2 = k * t;
    if (t > t2) {
        std::swap(t, t2);
    }
    std::uniform_real_distribution<T> unif_normal(t,t2);
    std::vector <T> res(2);
    res[0] = t;
    res[1] = t2;
    for (size_t i = 2; i < n; i++){
        res.push_back(unif_normal(generator));
    }
    std::sort(res.begin(), res.end());
    return res;
}
