#pragma once

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

    Vector Minimize() {
        auto g = OneMatrix(CurrentX.size());
        auto prevW = Func.GradApplier(CurrentX) * -1;
        auto P = prevW;
        auto a = search_methods(EPS).golden_ratio([this, &P](long double x) { return Func.FuncApplier(CurrentX + P * x); }, {-100, 100}).point;
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
            a = search_methods(EPS).golden_ratio([this, &P](long double x) { return Func.FuncApplier(CurrentX + P * x); }, {-100, 100}).point;
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
};

class TPowellMethod : public IQuasiNewtonMethod {
public:
    using IQuasiNewtonMethod::IQuasiNewtonMethod;

    Matrix CalcG(const Vector& v, const Vector& dw, const Vector& dx, const Matrix& g) override {
        auto dxDirection = dx + v;
        return g - VectorQuad(dxDirection) * (1 / (dw * dxDirection));
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