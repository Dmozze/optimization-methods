#pragma once

#include <algebra/Vector.h>
#include "LUMatrix.h"
#include <iostream>

inline Vector LUSolve(const LUMatrix &lu, Vector b) {
    Vector x(b.size());

    for (size_t i = 0; i < x.size(); i++) {
        x[i] = b[i];
        for (size_t j = 0; j < i; j++) {
            x[i] -= x[j] * lu.L(i + 1, j + 1);
        }
    }

    for (size_t i = x.size() - 1;; i--) {
        for (size_t j = i + 1; j < x.size(); j++) {
            x[i] -= lu.U(i + 1, j + 1) * x[j];
        }
        x[i] /= lu.U(i + 1, i + 1);
        if (i == 0) {
            break;
        }
    }
    return x;
}