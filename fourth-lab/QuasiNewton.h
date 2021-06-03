#pragma once

#include <algebra/Vector.h>
#include <algebra/Matrix.h>
#include "utils.h"

class IQuasiNewtonMethod {
    static constexpr bool GRAPHS = true;

public:
    explicit IQuasiNewtonMethod(FunctionData f, Vector startX)
        : Func(std::move(f))
        , CurrentX(std::move(startX)) {
    }

    FunctionData GetFunc() const {
        return Func;
    }

    virtual Vector Minimize() {
        auto g = OneMatrix(CurrentX.size());
        auto prevW = Func.GradApplier(CurrentX) * -1;
        auto P = prevW;
        auto minimize_func = [this, &P](long double x) { return Func.FuncApplier(CurrentX + P * x); };
        auto r = range(-1, 100);
        auto sm = search_methods(EPS);
        auto a = sm.golden_ratio(minimize_func, r).point;
        auto prevX = CurrentX;
        CurrentX += P * a;
        auto dx = CurrentX - prevX;
        ++IterCounter;
        if (GRAPHS) {
            std::cout << "(" << prevX[0] << ", " << prevX[1]
                      << ", " << dx[0] << ", " << dx[1]
                      << "),\n";
        }
        while (dx.Norm() >= EPS) {
            ++IterCounter;
            // std::cout << CurrentX << "\n";

            auto w = Func.GradApplier(CurrentX) * -1;
            auto dw = w - prevW;
            prevW = w;
            auto v = g * dw;
            g = CalcG(v, dw, dx, g);

            P = g * w;
            a = sm.golden_ratio(minimize_func, r).point;
            prevX = CurrentX;
            CurrentX += P * a;
            dx = CurrentX - prevX;
            if (GRAPHS) {
                std::cout << "(" << prevX[0] << ", " << prevX[1]
                          << ", " << dx[0] << ", " << dx[1]
                          << "),\n";
            }
        }
        return CurrentX;
    }

    virtual Matrix CalcG(const Vector& v, const Vector& dw, const Vector& dx, const Matrix& g) = 0;

    uint64_t IterCounter = 0;

protected:
    FunctionData Func;
    Vector CurrentX;
    static Matrix VectorQuad(const Vector& v) {
        return VectorMulVectorT(v, v);
    }

    // x.size() == y.size() !!!!
    static Matrix VectorMulVectorT(const Vector& x, const Vector& y) {
        Matrix m(x.size());
        for (size_t i = 0; i != x.size(); ++i) {
            for (size_t j = 0; j != x.size(); ++j) {
                m[i][j] = x[i] * y[j];
            }
        }
        return m;
    }
};

class TPowellMethod : public IQuasiNewtonMethod {
public:
    using IQuasiNewtonMethod::IQuasiNewtonMethod;

    Matrix CalcG(const Vector& v, const Vector& dw, const Vector& dx, const Matrix& g) override {
        auto dxDirection = dx + v;
        return g - VectorQuad(dxDirection) * (1 / (dw * dxDirection));
    }
};

class DFTMethod  {
public:

};