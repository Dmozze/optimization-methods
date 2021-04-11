#include "QuadraticFunction.h"


QuadraticFunction::QuadraticFunction(Matrix &A, Vector &b, QuadraticFunction::T c) : A(A), b(b), c(c){
}

QuadraticFunction::T QuadraticFunction::calc(Vector &x) {
    calc_history.push_back(x);
    T value = ((A * x) * x) / 2 + (b * x) + c;
    value_calc_history.push_back(value);
    return value;
}

Vector QuadraticFunction::gradient(Vector &x) {
    gradient_history.push_back(x);
    Vector value = (A * x) + b;
    value_gradient_history.push_back(value);
    return value;
}

Matrix QuadraticFunction::hessian() {
    return A;
}

information_methods QuadraticFunction::get_information_about_calculation() {
    return information_methods(calc_history,
                               value_calc_history,
                               gradient_history,
                               value_gradient_history);
}


