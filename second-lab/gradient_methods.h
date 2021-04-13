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

    void gradient_descent(QuadraticFunctionType &function, Vector &x0, T alpha) const {
        Vector x = x0;
        T f_x = function.calc(x);
        int cnt = 0;
        while (true) {
            cnt++;
            Vector gradient = function.gradient(x);
            T norma_gradient = gradient.norma();
            std::cout << norma_gradient << ' ';
            if (norma_gradient < epsilon) {
                break;
            }
            while (true) {
                Vector gradient_prod_alpha = gradient * alpha;
                Vector y = x - gradient_prod_alpha;
                std::cout << y << ' ';
                T f_y = function.calc(y);
                std::cout << f_y << '\n';
                if (f_y < f_x) {
                    x = y;
                    f_x = f_y;
                    break;
                }
                alpha /= 2;
            }
        }
        std::cout << "cnt descent: " << cnt << '\n';
    }

    void steepest_descent(QuadraticFunctionType &function, Vector x0, T L) const {
        search_methods searchMethods(epsilon);
        int cnt = 0;
        while (true) {
            cnt++;
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
//    std::vector<Vector> calc_history = function.get_calc_history();
//    std::vector<T> value_history = function.get_value_calc_history();
//    for (size_t i = 0; i < calc_history.size(); i++) {
//        std::cout << calc_history[i] << ' ' << value_history[i] << '\n';
//    }
        std::cout << "cnt steepest: " << cnt << '\n';
    }

    void conjugate_gradient(QuadraticFunctionType &function, Vector &x0) const {
        std::vector<Vector> p;
        Vector gradient0 = function.gradient(x0);
        p.emplace_back(gradient0 * (-1.0L));

        std::vector<Vector> x;
        x.emplace_back(x0);
        function.calc(x.back());

        Vector last_A_pk(x0.size());
        int cnt = 0;
        while (true) {
            cnt++;
            if (gradient0.norma() < epsilon) {
                break;
            }

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

        std::cout << "cnt conjugate: " << cnt << '\n';
    }

};

