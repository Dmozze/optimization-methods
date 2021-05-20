#pragma once
#include <utility>

#include "MatrixProfileFormat.h"

class LUMatrix : public MatrixProfileFormat {
    void toLUFormat();

public:
    LUMatrix(AL al, AU au, Diag diag, Profile profile)
        : MatrixProfileFormat(std::move(al),
                              std::move(au),
                              std::move(diag),
                              std::move(profile)) {
        toLUFormat();
    }

    explicit LUMatrix(Matrix matrix) : MatrixProfileFormat(std::move(matrix)) {
        toLUFormat();
    }


    explicit LUMatrix(MatrixProfileFormat profileMatrix) : MatrixProfileFormat(std::move(profileMatrix)) {
        toLUFormat();
    }

    T L(size_t i, size_t j) const;

    T U(size_t i, size_t j) const;

};

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

