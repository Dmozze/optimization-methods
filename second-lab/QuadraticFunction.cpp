#include "QuadraticFunction.h"

QuadraticFunction::QuadraticFunction(Matrix& A, Vector& b, QuadraticFunction::T c)
    : A(A)
    , b(b)
    , c(c) {
}

QuadraticFunction::T QuadraticFunction::calc(Vector& x) {
    // calc_history.push_back(x);
    T value = ((A * x) * x) / 2 + (b * x) + c;
    // value_calc_history.push_back(value);
    return value;
}

Vector QuadraticFunction::gradient(Vector& x) {
    //gradient_history.push_back(x);
    Vector value = (A * x) + b;
    //value_gradient_history.push_back(value);
    return value;
}

Matrix QuadraticFunction::hessian() {
    return A;
}

Vector QuadraticFunction::get_last_calc_vector() {
    return calc_history.back();
}

QuadraticFunction::T QuadraticFunction::get_last_calc_value() {
    return value_calc_history.back();
}

Vector QuadraticFunction::get_last_calc_gradient_vector() {
    return gradient_history.back();
}

Vector QuadraticFunction::get_last_calc_gradient_value() {
    return value_gradient_history.back();
}

QuadraticFunction::T QuadraticFunction::calc_without_history(Vector& x) {
    return ((A * x) * x) / 2 + (b * x) + c;
}
