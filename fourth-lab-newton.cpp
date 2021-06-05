#include <iostream>
#include "fourth-lab/utils.h"

#include "fourth-lab/Newton.h"

static void RunNewtonMethod(INewtonMethod& method) {
    auto v = method.Minimize();
    std::cout << "Method name: " << typeid(method).name() << "\n"
              << "Found answer:  " << v;
    std::cout << " f(x) = " << method.GetFunc().FuncApplier(v) << "\n";
    std::cout << "Iterations: " << method.IterCounter << "\n"
              << std::endl;
}

void RunAllMethods(FunctionData const& func, const Vector& start) {
    std::cout << "Start: ";
    std::cout << start << "\n";

    TBaseNewtonMethod simpleNewton(func, start);
    RunNewtonMethod(simpleNewton);

    TOneDimNewtonMethod oneDimNewton(func, start);
    RunNewtonMethod(oneDimNewton);

    TDescentNewtonMethod descentNewton(func, start);
    RunNewtonMethod(descentNewton);
}

using namespace Tests;

int main() {
    // TestSimpleQuadratic({-5, -2});
    TestPseudoNonQuadratic({0.1, 0});
    //TestPseudoNonQuadratic({-100, 200});
    //    TestF1({4, 1});
    // TestF2({-1.2, 1});
    // TestF2({0, 0});
    // TestF2({5, 5});
    //    TestF3({0, 0});
    //    TestF3({-5, -5});
    //    TestF3({2, 3});

    //  TestF4({1, 1, 1, 1});
    //  TestF4({-1, 0, -1, 0});
    // TestF4({1, 0, 0, 0});
    //    TestF5({0, 0});
    //    TestF5({5, 5});
    //    TestF5({-1, -1});
}
