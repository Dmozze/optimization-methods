#pragma once
#include <utility>
#include <vector>
#include <iostream>
#include <algebra/Vector.h>
#include "QuadraticFunction.h"
#include "../first-lab/search-metods.h"

template <typename QuadraticFunctionType>
class gradient_methods {
    using T = long double;
    T epsilon;

public:
    gradient_methods(T epsilon)
        : epsilon(epsilon){};

    size_t gradient_descent(QuadraticFunctionType& function, Vector& x0, T alpha) const {
        Vector x = x0;
        T f_x = function.calc(x);
        size_t cnt = 0;
        while (true) {
            Vector gradient = function.gradient(x);
            T norma_gradient = gradient.Norm();
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

    using type_search_method =
        std::function<information_search(std::function<T(T)>&, range)>;

    size_t steepest_descent(QuadraticFunctionType& function, Vector x0, const type_search_method& searchMethod) const {
        size_t cnt = 0;
        while (true) {
            Vector gradient = function.gradient(x0);
            if (gradient.Norm() < epsilon) {
                break;
            }
            cnt++;

            // Лямбда-функция для одномерной оптимизации
            std::function<T(T)> F = [&](T alpha) {
                Vector grad_alpha = gradient * alpha;
                Vector calc_vec = x0 - grad_alpha;
                return function.calc_without_history(calc_vec);
            };

            range rang(0, 0.1L);
            information_search informationSearch = searchMethod(F, rang);
            T alpha_min = informationSearch.point;
            Vector gradient_alpha_min = gradient * alpha_min;
            function.calc(x0);
            x0 = x0 - gradient_alpha_min;
        }
        return cnt;
    }

    size_t steepest_descent(QuadraticFunctionType& function, Vector x0) const {
        // Инициализирую методы одномерной оптимизации
        search_methods searchMethods(epsilon * epsilon);
        type_search_method combined_brent_method = [&](std::function<T(T)>& function1, range r) {
            return searchMethods.combined_brent(function1, std::move(r));
        };
        return steepest_descent(function, x0, combined_brent_method);
    }

    size_t conjugate_gradient(QuadraticFunctionType& function, Vector& x0) const {
        std::vector<Vector> p;
        Vector gradient0 = function.gradient(x0);
        p.emplace_back(gradient0 * (-1.0L));

        std::vector<Vector> x;
        x.emplace_back(x0);
        function.calc(x.back());

        Vector last_A_pk(x0.size());
        size_t cnt = 0;
        while (true) {
            if (gradient0.Norm() < epsilon) {
                break;
            }
            cnt++;
            Vector A_pk = function.hessian() * p.back();
            T A_pk_prod_pk = A_pk * p.back();
            T grad_norma_2 = gradient0 * gradient0;
            T alpha_k = grad_norma_2 / A_pk_prod_pk;

            Vector alpha_pk = p.back() * alpha_k;
            x.emplace_back(x.back() + alpha_pk);

            //Данное вычисление функции не влияет на ход алгоритма.
            //Это нужно только для статики.
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
