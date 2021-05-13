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
