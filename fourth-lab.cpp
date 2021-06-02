#include <iostream>
#include "fourth-lab/Newton.h"

namespace NewtonTests {

    static void RunNewtonMethod(INewtonMethod& method) {
        auto v = method.Minimize();
        for (auto&& el : v.data()) {
            std::cout << el << " ";
        }
        std::cout << "\n";
    }

    static void TestSimpleQuadratic() {
        std::cout << "Test simple quadratic func\n";
        FunctionData SimpleQuadraticFunc{
            [](auto& x) {
                return x[0] * x[0] + x[1] * x[1] - 3 * x[0] - 6 * x[1] + 10;
            },
            [](auto& x) {
                return Vector{2 * x[0] - 3, 2 * x[1] - 6};
            },
            [](auto& x) {
                return Matrix{{2, 0}, {0, 2}};
            }};
        TNewtonMethod simpleNewton(SimpleQuadraticFunc, {0, 0});
        RunNewtonMethod(simpleNewton);
        TOneDimNewtonMethod oneDimNewton(SimpleQuadraticFunc, {0, 0});
        RunNewtonMethod(oneDimNewton);
        TDescentNewtonMethod descentNewton(SimpleQuadraticFunc, {0, 0});
        RunNewtonMethod(descentNewton);
    }

    static void TestPseudoNonQuadratic() {
        std::cout << "Test simple pseudo non quadratic func \n";
        FunctionData NonQuadraticFunc{
            [](auto& x) {
                return x[0] * x[0] * x[0] * x[0] + x[1] * x[1] - 3 * x[0] * x[0] - 6 * x[1] + 10;
            },
            [](auto& x) {
                return Vector{4 * x[0] * x[0] * x[0] - 6 * x[0], 2 * x[1] - 6};
            },
            [](auto& x) {
                return Matrix{{12 * x[0] * x[0] - 6, 0}, {0, 2}};
            }};
        TNewtonMethod simpleNewton(NonQuadraticFunc, {0, 0});
        RunNewtonMethod(simpleNewton);
        TOneDimNewtonMethod oneDimNewton(NonQuadraticFunc, {0, 0});
        RunNewtonMethod(oneDimNewton);
        TDescentNewtonMethod descentNewton(NonQuadraticFunc, {0, 0});
        RunNewtonMethod(descentNewton);
    }
} // namespace NewtonTests

using namespace NewtonTests;

int main() {
    TestSimpleQuadratic();
    TestPseudoNonQuadratic();
}