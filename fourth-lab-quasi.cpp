#include <iostream>
#include <cmath>

#include "fourth-lab/Newton.h"
#include "fourth-lab/QuasiNewton.h"

namespace NewtonTests {
    static void RunNewtonMethod(IQuasiNewtonMethod& method) {
        auto v = method.Minimize();
        std::cout << "Method name: " << typeid(method).name() << "\n"
                  << "Found answer:  " << v;
        std::cout << " f(x) = " << method.GetFunc().FuncApplier(v) << "\n";
        std::cout << "Iterations: " << method.IterCounter << "\n"
                  << std::endl;
    }

    static void RunAllMethods(FunctionData const& func, const Vector& start = {0, 0}) {
        std::cout << "Start: ";
        for (auto&& el : start.data()) {
            std::cout << el << " ";
        }
        std::cout << "\n";

        TPowellMethod powellNewton(func, start);
        RunNewtonMethod(powellNewton);
    }

    static void TestF1() {
        std::cout << "Test F1: f(x) = 100 * (x2 - x1^2)^2 + (1-x1)^2, ans: (1, 1) \n";
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
    TestF1();
}