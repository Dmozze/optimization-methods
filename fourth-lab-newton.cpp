#include <iostream>
#include <cmath>

#include "fourth-lab/Newton.h"
#include "fourth-lab/QuasiNewton.h"

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
    TestF1();
    TestF2();
    TestF3();
}
