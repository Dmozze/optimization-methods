#pragma once

#include <algebra/Matrix.h>


inline Matrix hilbert_matrix_generator(size_t dim) {
    Matrix matrix(dim);
    for (int i = 0; i < (int)dim; i++) {
        for (int j = 0; j < (int)dim; j++) {
            matrix[i][j] = 1.0L/((i + 1) + (j + 1) - 1);
        }
    }
    return matrix;
}

inline MatrixProfileFormat hilbert_matrix_generator_profile_format(size_t dim) {
    return MatrixProfileFormat(hilbert_matrix_generator(dim));
}
