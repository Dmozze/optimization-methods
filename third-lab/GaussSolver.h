#pragma once
#include <algebra/Vector.h>
#include <algebra/Matrix.h>

inline Vector GaussSolve(Matrix a, Vector b) {
    size_t n = a.size() - 1;
    auto x = Vector{n + 1};
    for (size_t k = 0; k != n; ++k) {
        // choose pivot element:
        size_t m = k;
        for (size_t i = k; i != n + 1; ++i) {
            if (a[i][k] > a[m][k]) {
                m = i;
            }
        }
        if (a[m][k] == 0) {
            // todo: сравнивать с eps?
            throw std::invalid_argument("The system has endless solutions");
        } else if (k != m) {
            std::swap(b[k], b[m]);
            std::swap(a[k], a[m]);
        }

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