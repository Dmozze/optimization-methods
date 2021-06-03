#pragma once

#include <algebra/Vector.h>
#include <algebra/Matrix.h>
#include <functional>

inline constexpr long double EPS = 1e-7;
using Func = std::function<long double(Vector const&)>;
using Grad = std::function<Vector(Vector const&)>;
using Hess = std::function<Matrix(Vector const&)>;

struct FunctionData {
    Func FuncApplier;
    Grad GradApplier;
    Hess HessianApplier;
};

static inline Matrix OneMatrix(size_t len) {
    Matrix m(len);
    for (size_t i = 0; i != m.size(); ++i) {
        m[i][i] = 1;
    }
    return m;
}