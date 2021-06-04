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
    //TestSimpleQuadratic({-5, -2});
    //TestPseudoNonQuadratic({-100, 200});
    //TestF1({-1.2, 1});
    //TestF2({0, 0});
    // TestF3({2, 3});
    // TestF4({10, -10, 10, -10});
    TestF5({5, 5});
}
