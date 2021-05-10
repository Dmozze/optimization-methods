#include "LUMatrix.h"

#define place this->operator()

void LUMatrix::toLUFormat() {
    for (size_t i = 1; i <= dim(); i++) {
        for (size_t j = i + 1; j <= dim(); j++) {
            for (size_t k = i + 1; k <= dim(); k++) {
                set(j, k, place(j, k) - place(i, k) * place(j, i) / place(i, i));
            }
            set(j, i, place(j, i) / place(i, i));
        }
    }
}

MatrixProfileFormat::T LUMatrix::L(size_t i, size_t j) {
    if (i > j) {
        return place(i, j);
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
