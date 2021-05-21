#pragma once
#include <algebra/Vector.h>
#include <algebra/Matrix.h>

inline Vector GaussSolve(Matrix a, Vector b) {
    size_t n = a.size();
    std::vector<size_t> which_column(n, -1);
    size_t last_updated_row = 0;
    for (size_t i = 0; i != n && last_updated_row != n; ++i) {
        // опорный элемент
        size_t m = last_updated_row;
        for (size_t k = last_updated_row; k != n; ++k) {
            if (std::abs(a[k][i]) > std::abs(a[m][i])) {
                m = k;
            }
        }
        // прямой ход
        if (std::abs(a[m][i]) > 1e-9) {
            if (m != last_updated_row) {
                std::swap(a[m], a[last_updated_row]);
                std::swap(b[m], b[last_updated_row]);
            }
            which_column[i] = last_updated_row;
            for (size_t t = 0; t < n; ++t) {
                if (t != last_updated_row) {
                    long double coef = a[t][i] / a[last_updated_row][i];
                    for (size_t k = i; k < n; ++k) {
                        a[t][k] -= coef * a[last_updated_row][k];
                    }
                    b[t] -= coef * b[last_updated_row];
                }
            }
            ++last_updated_row;
        }
    }

    // обратный ход
    auto ans = Vector{a.size()};
    for (size_t i = 0; i < n; ++i) {
        if (which_column[i] != -1) {
            ans[i] = b[which_column[i]] / a[which_column[i]][i];
        }
    }
    return ans;
}