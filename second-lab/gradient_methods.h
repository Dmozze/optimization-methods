#pragma once
#include <vector>
#include "Vector.h"
#include "QuadraticFunction.h"


class gradient_methods {
    using T = long double;
    T epsilon;


public:

    gradient_methods(T epsilon) : epsilon(epsilon) {};

    void gradient_descent(QuadraticFunction &function, Vector &x0);

    void steepest_descent(QuadraticFunction &function);

    void conjugate_gradient(QuadraticFunction &function);

};

