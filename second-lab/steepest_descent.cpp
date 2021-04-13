#import "gradient_methods.h"
#include "../first-lab/search-metods.h"
#import <functional>

void gradient_methods::steepest_descent(QuadraticFunction &function, Vector x0, T L) {
    T f_x = function.calc(x0);
    search_methods searchMethods(epsilon);
    while (true) {
        Vector gradient = function.gradient(x0);
        if (gradient.norma() < epsilon) {
            break;
        }
        std::function<T(T)> F = [&](T alpha) {
            Vector grad_alpha = gradient * alpha;
            Vector calc_vec = x0 - grad_alpha;
            return function.calc(calc_vec);
        };

        range rang(0, 2.0L / L);
        information_search informationSearch = searchMethods.combined_brent(F, rang);
        T alpha_min = informationSearch.point;
        Vector gradient_alpha_min = gradient * alpha_min;
        x0 = x0 - gradient_alpha_min;
    }
}