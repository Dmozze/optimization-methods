#include <iostream>

#include <algebra/Vector.h>
#include "fourth-lab/QuasiNewton.h"
static void RunNewtonMethod(IQuasiNewtonMethod& method) {
    auto v = method.Minimize();
    std::cout << "Method name: " << typeid(method).name() << "\n"
              << "Found answer:  " << v;
    std::cout << " f(x) = " << method.GetFunc().FuncApplier(v) << "\n";
    std::cout << "Iterations: " << method.IterCounter << "\n"
              << std::endl;
}

void RunAllMethods(FunctionData const& func, const Vector& start) {
    std::cout << "Start: ";
    for (auto&& el : start.data()) {
        std::cout << el << " ";
    }
    std::cout << "\n";

    TPowellMethod powellNewton(func, start);
    RunNewtonMethod(powellNewton);

    DFTMethod dftMethod(func, start);
    RunNewtonMethod(dftMethod);
}

using namespace Tests;

int main() {
    //  TestF1();
    // TestF2({-1.2, 1});
    // TestF2({0, 0});
    //    TestF2({5, 5});
    TestF3({-4, 0});
    //    TestF3({-5, -5});
    //    TestF3({2, 3});
    // TestF4({1, 1, 1, 1});
    //    TestF4({-1, 0, -1, 0});
    //    TestF4({1, 0, 0, 0});

    //  TestF5({0, 0});
    //    TestF5({5, 5});
    //    TestF5({-1, -1});
    //TestF5({5, 5});
}