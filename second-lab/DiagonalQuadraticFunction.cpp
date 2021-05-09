#include "DiagonalQuadraticFunction.h"

DiagonalQuadraticFunction::DiagonalQuadraticFunction(DiagonalMatrix& A, Vector& b, DiagonalQuadraticFunction::T c)
    : A(A)
    , b(b)
    , c(c) {
}

DiagonalQuadraticFunction::T DiagonalQuadraticFunction::calc(Vector& x) {
    calc_history.push_back(x);
    T value = ((A * x) * x) / 2 + (b * x) + c;
    value_calc_history.push_back(value);
    return value;
}

Vector DiagonalQuadraticFunction::gradient(Vector& x) {
    gradient_history.push_back(x);
    Vector value = (A * x) + b;
    value_gradient_history.push_back(value);
    return value;
}

DiagonalMatrix DiagonalQuadraticFunction::hessian() {
    return A;
}

Vector DiagonalQuadraticFunction::get_last_calc_vector() {
    return calc_history.back();
}

DiagonalQuadraticFunction::T DiagonalQuadraticFunction::get_last_calc_value() {
    return value_calc_history.back();
}

Vector DiagonalQuadraticFunction::get_last_calc_gradient_vector() {
    return gradient_history.back();
}

Vector DiagonalQuadraticFunction::get_last_calc_gradient_value() {
    return value_gradient_history.back();
}

DiagonalQuadraticFunction::T DiagonalQuadraticFunction::calc_without_history(Vector& x) {
    return ((A * x) * x) / 2 + (b * x) + c;
    ;
}
