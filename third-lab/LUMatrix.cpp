#include <iostream>
#include "LUMatrix.h"

#define a this->operator()

void LUMatrix::toLUFormat() {
    for (size_t i = 1; i <= dim(); i++) {
        for (size_t j = i + 1; j <= dim(); j++) {
            for (size_t k = i + 1; k <= dim(); k++) {
                set(j, k, a(j, k) - a(i, k) * a(j, i) / a(i, i));;
            }
            set(j, i, a(j, i) / a(i, i));
        }
    }
}

MatrixProfileFormat::T LUMatrix::L(size_t i, size_t j) const {
    if (i > j) {
        return this->operator()(i, j);
    } else if (i == j) {
        return 1.0L;
    } else {
        return zero;
    }
}

MatrixProfileFormat::T LUMatrix::U(size_t i, size_t j) const {
    if (i <= j) {
        return this->operator()(i, j);
    } else {
        return zero;
    }
}
