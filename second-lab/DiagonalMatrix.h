#pragma once

#include <algebra/Vector.h>

class DiagonalMatrix {
    using T = long double;
    Vector diagonal;

public:
    DiagonalMatrix(Vector& vec)
        : diagonal(vec) {
    }

    size_t size() {
        return diagonal.size();
    }

    Vector operator*(Vector& vector) {
        Vector ans(size());
        for (size_t i = 0; i < size(); i++) {
            ans[i] = diagonal[i] * vector[i];
        }
        return ans;
    }

    Vector get_diagonal() {
        return diagonal;
    }
};
