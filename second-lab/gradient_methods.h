#pragma once
#include <vector>
#include <iostream>
#include "Vector.h"
#include "QuadraticFunction.h"
#include "../first-lab/search-metods.h"


template<typename QuadraticFunctionType>
class gradient_methods {
    using T = long double;
    T epsilon;


public:

    gradient_methods(T epsilon) : epsilon(epsilon) {};

    size_t gradient_descent(QuadraticFunctionType &function, Vector &x0, T alpha) const {
        Vector x = x0;
        T f_x = function.calc(x);
        size_t cnt = 0;
       // alpha = 0.1L;
        while (true) {
            Vector gradient = function.gradient(x);
            T norma_gradient = gradient.norma();
            if (norma_gradient < epsilon) {
                break;
            }
            cnt++;
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
        return cnt;
    }

    size_t steepest_descent(QuadraticFunctionType &function, Vector x0, T L) const {
        search_methods searchMethods(epsilon * epsilon);
        size_t cnt = 0;
        while (true) {
            Vector gradient = function.gradient(x0);
            if (gradient.norma() < epsilon) {
                break;
            }
            cnt++;
            std::function<T(T)> F = [&](T alpha) {
                Vector grad_alpha = gradient * alpha;
                Vector calc_vec = x0 - grad_alpha;
                return function.calc_without_history(calc_vec);
            };

            range rang(0, 0.1L);
            information_search informationSearch = searchMethods.combined_brent(F, rang);
            T alpha_min = informationSearch.point;
//            if (cnt % 100 == 0) {
//                std::cout << "2/L: " << 2.0L/L << " " << "alpha_min: ";
//                std::cout << alpha_min << " cnt_brent: " << informationSearch.times << '\n';
//            }
            Vector gradient_alpha_min = gradient * alpha_min;
            function.calc(x0);
            x0 = x0 - gradient_alpha_min;
        }
        return cnt;
    }

    size_t conjugate_gradient(QuadraticFunctionType &function, Vector &x0) const {
        std::vector<Vector> p;
        Vector gradient0 = function.gradient(x0);
        p.emplace_back(gradient0 * (-1.0L));

        std::vector<Vector> x;
        x.emplace_back(x0);
        function.calc(x.back());

        Vector last_A_pk(x0.size());
        size_t cnt = 0;
        while (true) {
            if (gradient0.norma() < epsilon) {
                break;
            }
            cnt++;
            Vector A_pk = function.hessian() * p.back();
            T A_pk_prod_pk = A_pk * p.back();
            T grad_norma_2 = gradient0 * gradient0;
            T alpha_k = grad_norma_2 / A_pk_prod_pk;

            Vector alpha_pk = p.back() * alpha_k;
            x.emplace_back(x.back() + alpha_pk);
            function.calc(x.back());

            Vector alpha_k_A_pk = A_pk * alpha_k;
            Vector gradient1 = gradient0 + alpha_k_A_pk;

            T bk = (gradient1 * gradient1) / (gradient0 * gradient0);

            Vector bk_pk = p.back() * bk;
            Vector antigradient = gradient1 * (-1.0L);
            p.emplace_back(antigradient + bk_pk);

            gradient0 = gradient1;
        }
        return cnt;
    }

};

