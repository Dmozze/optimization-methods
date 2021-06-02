#include <iostream>
#include "gradient_methods.h"

//void gradient_methods::gradient_descent(QuadraticFunctionType &function, Vector &x0, T alpha) const {
//    Vector x = x0;
//    T f_x = function.calc(x);
//    int cnt = 0;
//    while (true) {
//        cnt++;
//        Vector gradient = function.gradient(x);
//        T norma_gradient = gradient.Norm();
//        std::cout << norma_gradient << ' ';
//        if (norma_gradient < epsilon) {
//            break;
//        }
//        while (true) {
//            Vector gradient_prod_alpha = gradient * alpha;
//            Vector y = x - gradient_prod_alpha;
//            std::cout << y << ' ';
//            T f_y = function.calc(y);
//            std::cout << f_y << '\n';
//            if (f_y < f_x) {
//                x = y;
//                f_x = f_y;
//                break;
//            }
//            alpha /= 2;
//        }
//    }
//    std::cout << "cnt descent: " << cnt << '\n';
//}
