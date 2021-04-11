#pragma once
#include "Matrix.h"

class QuadraticFunction {

    using T = long double;


    Matrix A;
    Vector b;
    T c;

public:

    // A - симметричная положительно определенная матрица.
    QuadraticFunction(Matrix &A, Vector &b, T c);

    T calc(Vector &x);

    Vector gradient(Vector &x);

    Matrix hessian();



};


