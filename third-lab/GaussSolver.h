#pragma once
#include <algebra/Vector.h>
#include <algebra/Matrix.h>

inline Vector GaussSolve(Matrix a, Vector b) {
    size_t n = a.size() - 1;
    auto x = Vector{n + 1};
    for (size_t k = 0; k != n; ++k) {
        for (size_t i = k + 1; i != n + 1; ++i) {
            long double t = a[i][k] / a[k][k];
            b[i] -= t * b[k];
            for (size_t j = k + 1; j != n + 1; ++j) {
                a[i][j] -= t * a[k][j];
            }
        }
    }
    x[n] = b[n] / a[n][n];
    for (int64_t k = static_cast<int64_t>(n) - 1; k != -1; --k) {
        long double sum = 0;
        for (size_t j = k + 1; j != n + 1; ++j) {
            sum += a[k][j] * x[j];
        }
        x[k] = (b[k] - sum) / a[k][k];
    }
    return x;
}