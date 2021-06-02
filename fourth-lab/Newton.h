#pragma once
#include <utility>
#include <vector>
#include <functional>
#include <algebra/Vector.h>
#include <algebra/Matrix.h>

#include <GaussSolver.h>

inline constexpr long double EPS = 1e-7;
using Func = std::function<long double(Vector)>;
using Grad = std::function<Vector(Vector)>;
using Hess = std::function<Matrix(Vector)>;

struct FunctionData {
    Func FuncApplier;
    Grad GradApplier;
    Hess HessianApplier;
};

class INewtonMethod {
public:
    explicit INewtonMethod(FunctionData f, Vector startX)
        : Func(std::move(f))
        , CurrentX(std::move(startX)) {
    }

    virtual Vector Minimize() {
        while (true) {
            auto antigrad = -Func.GradApplier(CurrentX);
            if (antigrad.Norm() < EPS) {
                break;
            }
            P = CalcStep(Func.HessianApplier(CurrentX), antigrad);
            CurrentX += P * CalcScaling();
        }
        return CurrentX;
    }

    virtual Vector CalcStep(Matrix hessianValue, Vector antigrad) = 0;
    virtual long double CalcScaling() {
        return 1;
    }

protected:
    FunctionData Func;
    Vector CurrentX;
    Vector P;
};

class TNewtonMethod : public INewtonMethod {
public:
    using INewtonMethod::INewtonMethod;

    Vector CalcStep(Matrix hessianValue, Vector antigrad) override {
        return GaussSolve(hessianValue, antigrad);
    }
};

class TOneDimNewtonMethod : public INewtonMethod {
public:
    using INewtonMethod::INewtonMethod;

    Vector CalcStep(Matrix hessianValue, Vector antigrad) override {
        return GaussSolve(hessianValue, antigrad);
    }

    long double CalcScaling() override {
        return DichotomyMinimize([this](long double a) { return Func.FuncApplier(CurrentX + P * a); }, 0, 1000);
    }

private:
    template <typename FuncMinimize>
    long double DichotomyMinimize(FuncMinimize&& f, long double left, long double right) {
        long double x = 0;
        while (std::abs(right - left) > EPS) {
            x = (left + right) / 2;
            if (f(x - EPS) < f(x + EPS)) {
                right = x;
            } else {
                left = x;
            }
        }
        return x;
    }
};