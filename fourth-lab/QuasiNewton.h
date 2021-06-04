#pragma once

#include <algebra/Vector.h>
#include <algebra/Matrix.h>
#include "utils.h"

class IQuasiNewtonMethod {
    static constexpr bool GRAPHS = true;

public:
    explicit IQuasiNewtonMethod(FunctionData f, Vector startX)
        : Func(std::move(f))
        , CurrentX(std::move(startX))
        , X1(CurrentX)
        , G(OneMatrix(CurrentX.size())) {
    }

    FunctionData GetFunc() const {
        return Func;
    }

    virtual Vector Minimize() {
        iterate();
        while (p.Norm() > EPS) {
            iterate();
        }
        return CurrentX;
    }

    //    virtual Vector Minimize() {
    //        auto g = OneMatrix(CurrentX.size());
    //        auto prevW = Func.GradApplier(CurrentX) * -1;
    //        auto P = prevW;
    //        auto minimize_func = [this, &P](long double x) { return Func.FuncApplier(CurrentX + P * x); };
    //        auto r = range(-1000000, 1000000);
    //        auto sm = search_methods(EPS);
    //        auto a = sm.golden_ratio(minimize_func, r).point;
    //        std::cout << "a = " << a << std::endl;
    //        auto prevX = CurrentX;
    //        CurrentX += P * a;
    //        auto dx = CurrentX - prevX;
    //        ++IterCounter;
    //        if (GRAPHS) {
    //            std::cout << "(" << prevX[0] << ", " << prevX[1]
    //                      << ", " << dx[0] << ", " << dx[1]
    //                      << "),\n";
    //        }
    //        while (dx.Norm() >= EPS) {
    //            ++IterCounter;
    //            // std::cout << CurrentX << "\n";
    //
    //            auto w = Func.GradApplier(CurrentX) * -1;
    //            auto dw = w - prevW;
    //            prevW = w;
    //            auto v = g * dw;
    //            g = CalcG(v, dw, dx, g);
    //
    //            P = g * w;
    //            a = sm.golden_ratio(minimize_func, r).point;
    //           // std::cout << "a = " << a << std::endl;
    //            prevX = CurrentX;
    //            CurrentX += P * a;
    //            dx = CurrentX - prevX;
    //            if (GRAPHS) {
    //                std::cout << "(" << prevX[0] << ", " << prevX[1]
    //                          << ", " << dx[0] << ", " << dx[1]
    //                          << "),\n";
    //            }
    //        }
    //        return CurrentX;
    //    }

    virtual Matrix CalcG(const Vector& v, const Vector& dw, const Vector& dx, const Matrix& g) = 0;

    uint64_t IterCounter = 0;

protected:
    FunctionData Func;
    Vector CurrentX;
    Vector X1;
    Vector p;
    Vector s;
    long double alpha = 0;
    Matrix G;

    void iterate() {
        ++IterCounter;
        auto g = Func.GradApplier(CurrentX) * -1;
        p = G * g;
        alpha = search_methods(EPS).golden_ratio([this](long double x) { return Func.FuncApplier(CurrentX + p * x); }, {-10, 10}).point;
        s = p * alpha;
       // std::cout << "alpha = " << alpha << std::endl;
        auto dx = p * alpha;
        X1 = CurrentX;
        CurrentX += dx;
        auto w = Func.GradApplier(CurrentX) - Func.GradApplier(X1);
        auto dx_ = dx + G * w;
        G = G - VectorQuad(dx_) * (1 / (w * dx_));
        if (GRAPHS) {
            std::cout << "(" << X1[0] << ", " << X1[1]
                      << ", " << dx[0] << ", " << dx[1]
                      << "),\n";
        }
    }

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

class DFTMethod {
public:
};