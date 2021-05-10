#include "LUMatrix.h"

void LUMatrix::toLUFormat() {
    for (size_t i = 1; i <= dim(); i++) {
        for (size_t j = i + 1; j <= dim(); j++) {
            for (size_t k = i + 1; k <= dim(); k++) {
                set(j, k, this->operator()(j, k) - this->operator()(i, k) * this->operator()(j, i) / this->operator()(i, i));
            }
            set(j, i, this->operator()(j, i) / this->operator()(i, i));
        }
    }
}

MatrixProfileFormat::T LUMatrix::L(size_t i, size_t j) {
    if (i > j) {
        return this->operator()(i, j);
    } else if (i == j) {
        return 1.0L;
    } else {
        return zero;
    }
}

MatrixProfileFormat::T LUMatrix::U(size_t i, size_t j) {
    if (i <= j) {
        return this->operator()(i, j);
    } else {
        return zero;
    }
}
