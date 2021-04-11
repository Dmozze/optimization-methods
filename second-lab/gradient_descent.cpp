#import "gradient_methods.h"


information_methods gradient_methods::gradient_descent(QuadraticFunction &function, Vector &x0) {
    T alpha = 0.01L; //разобраться откуда брать эту константу нормально.
    Vector x = x0;
    T f_x = function.calc(x);
    while (true) {
        Vector gradient = function.gradient(x);
        T norma_gradient = gradient.norma();
        if (norma_gradient < epsilon) {
            break;
        }
        while (true) {
            Vector gradient_prod_alpha = gradient * alpha;
            Vector y = x - gradient_prod_alpha;
            T f_y = function.calc(y);
            if (f_y < f_x) {
                x = y;
                f_x = f_y;
                break;
            }
            alpha /= 2;
        }
    }
    return function.get_information_about_calculation();
}

