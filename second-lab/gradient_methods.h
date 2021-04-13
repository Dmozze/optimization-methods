#pragma once
#include <vector>
#include "Vector.h"
#include "QuadraticFunction.h"


class gradient_methods {
    using T = long double;
    T epsilon;


public:

    gradient_methods(T epsilon) : epsilon(epsilon) {};

    void gradient_descent(QuadraticFunction &function, Vector &x0, T alpha) const;

    void steepest_descent(QuadraticFunction &function, Vector x0, T L) const;

    void conjugate_gradient(QuadraticFunction &function, Vector &x0) const;

};

