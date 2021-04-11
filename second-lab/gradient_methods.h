

#include <vector>
#include "Vector.h"
#include "QuadraticFunction.h"


struct information_methods {
    using T = long double;
    std::vector<Vector> history_points{};
    std::vector<T> values_points{};
    std::vector<Vector> gradient_history{};
    std::vector<Vector> values_gradient_history{};

    information_methods(std::vector<Vector> &history_points,
                        std::vector<T> &values_points,
                        std::vector<Vector> &gradient_history,
                        std::vector<Vector> &values_gradient_history)
                        :
                        history_points(history_points),
                        values_points(values_points),
                        gradient_history(gradient_history),
                        values_gradient_history(values_gradient_history)
                        {
    }
};

class gradient_methods {
    using T = long double;
    T epsilon;


public:

    gradient_methods(T epsilon) : epsilon(epsilon) {};

    information_methods gradient_descent(QuadraticFunction &function, Vector &x0);

    information_methods steepest_descent(QuadraticFunction &function);

    information_methods conjugate_gradient(QuadraticFunction &function);

};

