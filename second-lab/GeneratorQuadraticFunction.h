#include "Vector.h"

class generator_quadratic_functions {
    using T = long double;
    std::vector<T> gen_quad(size_t n, T k);
    Vector generateVector(size_t n) {
        return Vector(gen_quad(n, 1000.0L));
    }

};


