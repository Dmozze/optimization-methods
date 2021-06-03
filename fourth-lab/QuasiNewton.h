#pragma once

#include "utils.h"

class IQuasiNewtonMethod {
public:
    explicit IQuasiNewtonMethod(FunctionData f, Vector startX)
        : Func(std::move(f))
        , CurrentX(std::move(startX)) {
    }

    Vector Minimize() {
        auto g = OneMatrix(CurrentX.size());
        auto prevW = Func.GradApplier(CurrentX) * -1;
        long double a = search_methods(EPS).golden_ratio([&](long double a) { return Func.FuncApplier(CurrentX + prevW * a); }, {-100, 100}).point;
        auto prevX = CurrentX;
        CurrentX += prevW * a;
        auto dx = CurrentX - prevX;
        while (dx.Norm() > EPS) {
            ++IterCounter;

            auto w = Func.GradApplier(CurrentX) * -1;
            auto dw = w - prevW;
            prevW = w;

            g = CalcG(g * dw, dw, dx, g);
            a = search_methods(EPS).golden_ratio([&](long double a) { return Func.FuncApplier(CurrentX + g * dw * a); }, {-100, 100}).point;

            prevX = CurrentX;
            CurrentX += g * w * a;
            dx = CurrentX - prevX;
        }
        return CurrentX;
    }

    virtual Matrix CalcG(const Vector& v, const Vector& dw, const Vector& dx, const Matrix& g) = 0;

    uint64_t IterCounter = 0;

protected:
    FunctionData Func;
    Vector CurrentX;
};

class TPowellMethod : public IQuasiNewtonMethod {
public:
    using IQuasiNewtonMethod::IQuasiNewtonMethod;

    Matrix CalcG(const Vector& v, const Vector& dw, const Vector& dx, const Matrix& g) override {
        auto dxDirection = dx + v;
        return g - VectorQuad(dxDirection) * (1 / (dw * dx));
    }

private:
    static Matrix VectorQuad(const Vector& v) {
        Matrix m(v.size());
        for (size_t i = 0; i != v.size(); ++i) {
            for (size_t j = 0; j != v.size(); ++j) {
                m[i][j] = v[i] * v[j];
            }
        }
        return m;
    }
};