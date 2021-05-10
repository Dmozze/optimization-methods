#pragma once
#include <algebra/Vector.h>
#include "LUMatrix.h"
#include <iostream>

inline Vector LUSolve(LUMatrix lu, Vector b) {
    Vector x(b.size());

    for (size_t i = 1; i < x.size(); i++) {
        x[i] = b[i];
        for (size_t j = 1; j < i; j++) {
            x[i] -= x[j] * lu.L(i, j);
        }
    }

    for (size_t i = x.size() - 1; i > 0; i--) {
        for (size_t j = i + 1; j < x.size(); j++) {
            x[i] -= lu.U(i, j) * x[j];
        }
        x[i] /= lu.U(i, i);
    }
    return x;
}