#include "gradient_methods.h"
#include "../first-lab/search-metods.h"
#include <functional>
//
//void gradient_methods::steepest_descent(QuadraticFunctionType &function, Vector x0, T L) const {
//    search_methods searchMethods(epsilon);
//    int cnt = 0;
//    while (true) {
//        cnt++;
//        Vector gradient = function.gradient(x0);
//        if (gradient.norma() < epsilon) {
//            break;
//        }
//        std::function<T(T)> F = [&](T alpha) {
//            Vector grad_alpha = gradient * alpha;
//            Vector calc_vec = x0 - grad_alpha;
//            return function.calc(calc_vec);
//        };
//
//        range rang(0, 2.0L / L);
//        information_search informationSearch = searchMethods.combined_brent(F, rang);
//        T alpha_min = informationSearch.point;
//        Vector gradient_alpha_min = gradient * alpha_min;
//        x0 = x0 - gradient_alpha_min;
//    }
////    std::vector<Vector> calc_history = function.get_calc_history();
////    std::vector<T> value_history = function.get_value_calc_history();
////    for (size_t i = 0; i < calc_history.size(); i++) {
////        std::cout << calc_history[i] << ' ' << value_history[i] << '\n';
////    }
//    std::cout << "cnt steepest: " << cnt << '\n';
//}