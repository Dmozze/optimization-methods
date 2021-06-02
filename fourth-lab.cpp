#include <iostream>
#include <cmath>

#include "fourth-lab/Newton.h"

namespace NewtonTests {
    static void RunNewtonMethod(INewtonMethod& method) {
        std::cout << "Method name: " << typeid(method).name() << "\n"
                  << "Found answer: ";
        auto v = method.Minimize();
        for (auto&& el : v.data()) {
            std::cout << el << " ";
        }
        std::cout << "\n";
        std::cout << "Iterations: " << method.IterCounter << "\n"
                  << std::endl;
    }

    static void RunAllMethods(FunctionData const& func, const Vector& start = {0, 0}) {
        std::cout << "Start: ";
        for (auto&& el : start.data()) {
            std::cout << el << " ";
        }
        std::cout << "\n";

        TBaseNewtonMethod simpleNewton(func, start);
        RunNewtonMethod(simpleNewton);

        TOneDimNewtonMethod oneDimNewton(func, start);
        RunNewtonMethod(oneDimNewton);

        TDescentNewtonMethod descentNewton(func, start);
        RunNewtonMethod(descentNewton);
    }

    static void TestSimpleQuadratic() {
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
             }});
    }

    static void TestPseudoNonQuadratic() {
        std::cout << "Test simple pseudo non quadratic func \n";
        RunAllMethods({[](auto& x) {
                           return x[0] * x[0] * x[0] * x[0] + x[1] * x[1] - 3 * x[0] * x[0] - 6 * x[1] + 10;
                       },
                       [](auto& x) {
                           return Vector{4 * x[0] * x[0] * x[0] - 6 * x[0], 2 * x[1] - 6};
                       },
                       [](auto& x) {
                           return Matrix{{12 * x[0] * x[0] - 6, 0}, {0, 2}};
                       }});
    }

    static void TestF1() {
        std::cout << "Test F1: f(x) = x1^2 + x2^2 - 2 * x1 * x2, ans: (0, 0) \n";
        RunAllMethods(
            {[](auto& x) { return x[0] * x[0] + x[1] * x[1] - 1.2 * x[0] * x[1]; },
             [](auto& x) {
                 return Vector{2 * x[0] - 1.2 * x[1], 2 * x[1] - 1.2 * x[0]};
             },
             [](auto& x) {
                 return Matrix{{2, -1.2}, {-1.2, 2}};
             }},
            {4, 1});
    }

    static void TestF2() {
        std::cout << "Test F2: f(x) = 100 * (x2 - x1^2)^2 + (1-x1)^2, ans: (1, 1) \n";
        RunAllMethods(
            {[](auto& x) { return 100 * std::pow(x[1] - x[0] * x[0], 2) + std::pow(1 - x[0], 2); },
             [](auto& x) {
                 return Vector{
                     -400 * x[0] * (x[1] - x[0] * x[0]) - 2 * (1 - x[0]),
                     200 * (x[1] - x[0] * x[0])};
             },
             [](auto& x) {
                 return Matrix{{-400 * (x[1] - x[0] * x[0]) + 800 * x[0] * x[0] + 2, -400 * x[0]},
                               {-400 * x[0], 200}};
             }},
            {-1.2, 1});
    }
} // namespace NewtonTests

using namespace NewtonTests;

int main() {
    //    TestSimpleQuadratic();
    //    TestPseudoNonQuadratic();
    TestF1();
    TestF2();
}