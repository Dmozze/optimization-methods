

#include <vector>
#include "Vector.h"
#include "QuadraticFunction.h"


class information_methods {
    using T = long double;
    std::vector<Vector> history_points{};
    std::vector<T> values_points{};

public:

    information_methods(Vector &start) {
        history_points.push_back(start);
    }

    Vector get_last_point() {
        return history_points.back();
    }

    void add_point(Vector &vector) {
        history_points.push_back(vector);
    }

};

class gradient_methods {
    using T = long double;
    T epsilon;


public:

    gradient_methods(T epsilon) : epsilon(epsilon) {};

    information_methods gradient_descent(QuadraticFunction &function);

    information_methods steepest_descent(QuadraticFunction &function);

    information_methods conjugate_gradient(QuadraticFunction &function);

};

