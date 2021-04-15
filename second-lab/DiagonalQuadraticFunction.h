#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "DiagonalMatrix.h"

class DiagonalQuadraticFunction {

    using T = long double;
    DiagonalMatrix A;
    Vector b;
    T c;
    std::vector<Vector> calc_history;
    std::vector<Vector> gradient_history;

    std::vector<T> value_calc_history;
    std::vector<Vector> value_gradient_history;


public:

    // A - диагональная матрица ввиде вектора
    DiagonalQuadraticFunction(DiagonalMatrix &A, Vector &b, T c);

    T calc(Vector &x);

    T calc_without_history(Vector &x);

    Vector gradient(Vector &x);

    DiagonalMatrix hessian();

    Vector get_last_calc_vector();

    T get_last_calc_value();

    Vector get_last_calc_gradient_vector();

    Vector get_last_calc_gradient_value();

    std::vector<Vector> get_calc_history() {
        return calc_history;
    }

    std::vector<Vector> get_gradient_history() {
        return gradient_history;
    }

    std::vector<T> get_value_calc_history() {
        return value_calc_history;
    }

    std::vector<Vector> get_value_gradient_history() {
        return value_gradient_history;
    }

    Vector get_b() {
        return b;
    }

    T get_c() {
        return c;
    }
};



