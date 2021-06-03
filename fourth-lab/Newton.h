#pragma once
#include "utils.h"

#include <GaussSolver.h>
#include <search-metods.h>

#include <utility>
#include <vector>
#include <functional>
#include <algebra/Vector.h>
#include <algebra/Matrix.h>

class INewtonMethod {
    static constexpr bool GRAPHS = true;

public:
    explicit INewtonMethod(FunctionData f, Vector startX)
        : Func(std::move(f))
        , CurrentX(std::move(startX)) {
    }

    Vector Minimize() {
        while (true) {
            auto antigrad = -Func.GradApplier(CurrentX);
            if (antigrad.Norm() < EPS) { // todo: сравнивать дельту между шагами
                break;
            }
            ++IterCounter;
            P = CalcStep(Func.HessianApplier(CurrentX), antigrad);
            if (GRAPHS) {
                std::cout << "(" << CurrentX[0] << ", " << CurrentX[1]
                          << ", " << (P * CalcScaling())[0] << ", " << (P * CalcScaling())[1]
                          << "),\n";
            }
            CurrentX += P * CalcScaling();
        }
        return CurrentX;
    }

    FunctionData GetFunc() const {
        return Func;
    }

    virtual Vector CalcStep(const Matrix& hessianValue, const Vector& antigrad) = 0;
    virtual long double CalcScaling() {
        return 1;
    }

    uint64_t IterCounter = 0;

protected:
    FunctionData Func;
    Vector CurrentX;
    Vector P;
};

class TBaseNewtonMethod : public INewtonMethod {
public:
    using INewtonMethod::INewtonMethod;

    Vector CalcStep(const Matrix& hessianValue, const Vector& antigrad) override {
        return GaussSolve(hessianValue, antigrad);
    }
};

class TOneDimNewtonMethod : public INewtonMethod {
public:
    using INewtonMethod::INewtonMethod;

    Vector CalcStep(const Matrix& hessianValue, const Vector& antigrad) override {
        return GaussSolve(hessianValue, antigrad);
    }

    long double CalcScaling() override {
        auto f = [this](long double a) { return Func.FuncApplier(CurrentX + P * a); };
        return search_methods(EPS).golden_ratio(f, {-100, 100}).point;
    }
    // todo: не понятно ,какие границы для альфа
    //          мне сказали, что при положительных может не сходиться, хотя это странно

private:
    template <typename FuncMinimize>
    long double GoldenRatioMinimize(FuncMinimize&& f, long double left, long double right) {
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

class TDescentNewtonMethod : public TOneDimNewtonMethod {
public:
    using TOneDimNewtonMethod::TOneDimNewtonMethod;

    Vector CalcStep(const Matrix& hessianValue, const Vector& antigrad) override {
        auto step = TOneDimNewtonMethod::CalcStep(hessianValue, antigrad);
        if (antigrad * step < 0) {
            return antigrad;
        } else {
            return step;
        }
    }
};