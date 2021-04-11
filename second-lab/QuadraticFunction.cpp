#include "QuadraticFunction.h"


QuadraticFunction::QuadraticFunction(Matrix &A, Vector &b, QuadraticFunction::T c) : A(A), b(b), c(c){
}

QuadraticFunction::T QuadraticFunction::calc(Vector &x) {
    return ((A * x) * x) / 2 + (b * x) + c;
}

Vector QuadraticFunction::gradient(Vector &x) {
    return (A * x) + b;
}

Matrix QuadraticFunction::hessian() {
    return A;
}


