#pragma once

#include <cmath>
#include <algebra/Vector.h>
#include <algebra/Matrix.h>
#include <functional>
#include <search-metods.h>

static constexpr bool GRAPHS = true;
inline constexpr long double EPS = 1e-7;
using Func = std::function<long double(Vector const&)>;
using Grad = std::function<Vector(Vector const&)>;
using Hess = std::function<Matrix(Vector const&)>;

struct FunctionData {
    Func FuncApplier;
    Grad GradApplier;
    Hess HessianApplier;
};

static void gradient_descent(const FunctionData& function, const Vector& x0, long double alpha) {
    Vector x = x0;
    auto f_x = function.FuncApplier(x);
    int cnt = 0;
    while (true) {
        cnt++;
        Vector gradient = function.GradApplier(x);
        auto norma_gradient = gradient.Norm();
        std::cout << norma_gradient << ' ';
        if (norma_gradient < EPS) {
            break;
        }
        while (true) {
            Vector gradient_prod_alpha = gradient * alpha;
            Vector y = x - gradient_prod_alpha;
            std::cout << y << ' ';
            auto f_y = function.FuncApplier(y);
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

static void steepest_descent(const FunctionData& function, Vector x0, long double bound) {
    search_methods searchMethods(EPS);
    std::cout << "Steepest descent\n";
    int cnt = 0;
    while (true) {
        cnt++;
        Vector gradient = function.GradApplier(x0);
        if (gradient.Norm() < EPS) {
            break;
        }
        auto F = [=](auto alpha) {
            Vector grad_alpha = gradient * alpha;
            Vector calc_vec = x0 - grad_alpha;
            return function.FuncApplier(calc_vec);
        };

        std::cout << gradient;
        range rang(0, bound);
        information_search informationSearch = searchMethods.golden_ratio(F, rang);
        auto alpha_min = informationSearch.point;
        Vector gradient_alpha_min = gradient * alpha_min;
        std::cout << gradient_alpha_min;

        if (GRAPHS) {
            std::cout << "(" << x0[0] << ", " << x0[1]
                      << ", " << -gradient_alpha_min[0] << ", " << -gradient_alpha_min[1]
                      << "),\n";
        }
        x0 = x0 - gradient_alpha_min;
    }
    //    std::vector<Vector> calc_history = function.get_calc_history();
    //    std::vector<T> value_history = function.get_value_calc_history();
    //    for (size_t i = 0; i < calc_history.size(); i++) {
    //        std::cout << calc_history[i] << ' ' << value_history[i] << '\n';
    //    }
    std::cout << "cnt steepest: " << cnt << '\n';
}
static inline Matrix OneMatrix(size_t len) {
    Matrix m(len);
    for (size_t i = 0; i != m.size(); ++i) {
        m[i][i] = 1;
    }
    return m;
}

void RunAllMethods(FunctionData const& func, const Vector& start = {0, 0});

namespace Tests {
    static void TestSimpleQuadratic(const Vector& start = {0, 0}) {
        std::cout << "Test simple quadratic func\n";
        RunAllMethods(
            {[](auto& x) {
                 return x[0] * x[0] + x[1] * x[1] - 3 * x[0] - 6 * x[1] + 10;
             },
             [](auto& x) {
                 return Vector{2 * x[0] - 3, 2 * x[1] - 6};
             },
             [](auto& x) {
                 return Matrix{{2, 0}, {0, 2}};
             }},
            start);
    }

    static void TestPseudoNonQuadratic(const Vector& start = {0, 0}) {
        std::cout << "Test simple pseudo non quadratic func \n";
        RunAllMethods({[](auto& x) {
                           return x[0] * x[0] * x[0] * x[0] + x[1] * x[1] - 3 * x[0] * x[0] - 6 * x[1] + 10;
                       },
                       [](auto& x) {
                           return Vector{4 * x[0] * x[0] * x[0] - 6 * x[0], 2 * x[1] - 6};
                       },
                       [](auto& x) {
                           return Matrix{{12 * x[0] * x[0] - 6, 0}, {0, 2}};
                       }},
                      start);
    }

    static void TestF1(const Vector& start = {4, 1}) {
        std::cout << "Test F1: f(x) = x1^2 + x2^2 - 2 * x1 * x2, ans: (0, 0) \n";
        RunAllMethods(
            {[](auto& x) { return x[0] * x[0] + x[1] * x[1] - 1.2 * x[0] * x[1]; },
             [](auto& x) {
                 return Vector{2 * x[0] - 1.2 * x[1], 2 * x[1] - 1.2 * x[0]};
             },
             [](auto& x) {
                 return Matrix{{2, -1.2}, {-1.2, 2}};
             }},
            start);
    }

    static void TestF2(const Vector& start = {-1.2, 1}) {
        std::cout << "Test F2: f(x) = 100 * (x2 - x1^2)^2 + (1-x1)^2, ans: (1, 1) \n";
        RunAllMethods(
            {[](auto& x) { return 100 * std::pow(x[1] - x[0] * x[0], 2) + std::pow(1 - x[0], 2); },
             [](auto& x) {
                 return Vector{
                     400 * x[0] * x[0] * x[0] - 400 * x[0] * x[1] - 2 + 2 * x[0],
                     200 * x[1] - 400 * x[0] * x[0]};
             },
             [](auto& x) {
                 return Matrix{{-400 * (x[1] - x[0] * x[0]) + 800 * x[0] * x[0] + 2, -400 * x[0]},
                               {-400 * x[0], 200}};
             }},
            start);
    }

    static void TestF3(const Vector& start = {0, 0}) {
        std::cout << "Test F3: f(x) = (x_1^2 + x_2 − 11)^2 + (x_1 + x_2^2 − 7)^2, ans: (3, 2), (-3.77931, -3.28319),  (-2.80512, 3.13131), (3.58443, -1.84813) \n";
        RunAllMethods(
            {[](auto& x) { return (x[0] * x[0] + x[1] - 11) * (x[0] * x[0] + x[1] - 11) + (x[0] + x[1] * x[1] - 7) * (x[0] + x[1] * x[1] - 7); },
             [](auto& x) {
                 return Vector{
                     4 * x[0] * x[0] * x[0] + 4 * x[0] * x[1] - 42 * x[0] + 2 * x[1] * x[1] - 14,
                     2 * x[0] * x[0] + 4 * x[0] * x[1] + 4 * x[1] * x[1] * x[1] - 26 * x[1] - 22};
             },
             [](auto& v) {
                 auto x = v[0];
                 auto y = v[1];
                 return Matrix{{12 * x * x + 4 * y - 42, 4 * x + 4 * y},
                               {4 * x + 4 * y, 4 * x + 12 * y * y - 26}};
             }},
            start);
    }

    static void TestF4(const Vector& start = {0, 0, 0, 0}) {
        std::cout << "Test F4: f(x) = (x_1 + 10x_2)^2 + 5(x_3 − x_4)^2 + (x_2 − 2x_3)^4 + 10(x_1 − x_4)^4 \n";
        RunAllMethods(
            {[](auto& x) { return std::pow(x[0] + 10 * x[1], 2) + 5 * std::pow(x[2] - x[3], 2) +
                                  std::pow(x[1] - 2 * x[2], 4) + 10 * std::pow(x[0] - x[3], 2); },
             [](auto& x) {
                 double x1 = x[0];
                 double x2 = x[1];
                 double x3 = x[2];
                 double x4 = x[3];
                 return Vector{-40 * x4 * x4 * x4 + 120 * x4 * x4 * x1 - 120 * x4 * x1 * x1 + 40 * x1 * x1 * x1 + 2 * x1 + 20 * x2,
                               20 * (x1 + 10 * x2) + 4 * std::pow((x2 - 2 * x3), 3),
                               -10 * x4 - 8 * x2 * x2 * x2 + 48 * x2 * x2 * x3 - 96 * x2 * x3 * x3 + 64 * x3 * x3 * x3 + 10 * x3,
                               -40 * std::pow(x1 - x4, 3) + 10 * x4 - 10 * x3};
             },
             [](auto& v) {
                 double x = v[0];
                 double y = v[1];
                 double z = v[2];
                 double k = v[3];
                 return Matrix{
                     {2 * (60 * (x - k) * (x - k) + 1), 20.0, 0.0, -120 * (x - k) * (x - k)},
                     {20.0, 4 * (3 * (y - 2 * z) * (y - 2 * z) + 50), -24 * (y - 2 * z) * (y - 2 * z), 0.0},
                     {0.0, -24 * (y - 2 * z) * (y - 2 * z), 48 * (y - 2 * z) * (y - 2 * z) + 10, -10.},
                     {-120 * (x - k) * (x - k), 0., -10., 10 * (12 * (x - k) * (x - k) + 1)}};
             }},
            start);
    }

    static void TestF5(const Vector& start = {0, 0}) {
        std::cout << "Test F5: f(x) = 100 − \\frac{2} {1+(\\frac{x_1−1} {2})^2 +(\\frac{x_2−1}{3})^2} − \\frac{1}{1+(\\frac{x_1−2}{2})^2 +(\\frac{x_2−1}{3})^2}, ans: (1.29164, 1)  \n";
        RunAllMethods(
            {[](auto& x) { return 100 - 2 / (1 + std::pow((x[0] - 1) / 2, 2) + std::pow((x[1] - 1) / 3, 2)) -
                                  1 / (1 + std::pow((x[0] - 2) / 2, 2) + std::pow((x[1] - 1) / 3, 2)); },
             [](auto& v) {
                 double x = v[0];
                 double y = v[1];
                 double one = std::pow(std::pow(x - 2, 2) / 4 + std::pow(y - 1, 2) / 9 + 1, 2);
                 double two = std::pow(std::pow(x - 1, 2) / 4 + std::pow(y - 1, 2) / 9 + 1, 2);
                 return Vector{(x - 2) / (2 * one) + (x - 1) / two,
                               ((2 * (y - 1)) / 9) * (2 / two + 1 / one)};
             },
             [](auto& v) {
                 double x = v[0];
                 double y = v[1];
                 double one = std::pow(x - 2, 2) / 4 + std::pow(y - 1, 2) / 9 + 1;
                 double two = std::pow(x - 1, 2) / 4 + std::pow(y - 1, 2) / 9 + 1;
                 return Matrix{
                     {-std::pow(x - 2, 2) / (2 * std::pow(one, 3)) + 1 / (2 * one * one) + 1 / (two * two) - std::pow(x - 1, 2) / std::pow(two, 3),
                      (-2 * (x - 2) * (y - 1)) / (9 * std::pow(one, 3)) - (4 * (x - 1) * (y - 1)) / (9 * std::pow(two, 3))},
                     {(-2 * (x - 2) * (y - 1)) / (9 * std::pow(one, 3)) - (4 * (x - 1) * (y - 1)) / (9 * std::pow(two, 3)),
                      (-8 * std::pow(y - 1, 2)) / (81 * std::pow(one, 3)) - (16 * std::pow(y - 1, 2)) / (81 * std::pow(two, 3)) + 2 / (9 * one * one) + 4 / (9 * two * two)}};
             }},
            start);
    }
} // namespace Tests