#pragma once
#include "Matrix.h"


class QuadraticFunction {

    using T = long double;
    Matrix A;
    Vector b;
    T c;
    std::vector<Vector> calc_history;
    std::vector<Vector> gradient_history;

    std::vector<T> value_calc_history;
    std::vector<Vector> value_gradient_history;


public:

    // A - симметричная положительно определенная матрица.
    QuadraticFunction(Matrix &A, Vector &b, T c);

    T calc(Vector &x);

    Vector gradient(Vector &x);

    Matrix hessian();

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

};


