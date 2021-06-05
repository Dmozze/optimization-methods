#pragma once

#include "utils.h"

#include <GaussSolver.h>
#include <search-metods.h>

#include <utility>
#include <vector>
#include <functional>
#include <algebra/Vector.h>
#include <algebra/Matrix.h>
#include <ConjugateSolver.h>

class IMarkvardMethod {
    static constexpr bool GRAPHS = true;

public:
    explicit IMarkvardMethod(FunctionData f, Vector startX, long double tau)
        : Func(std::move(f))
        , CurrentX(std::move(startX))
        , Tau(tau) {
    }

    virtual Vector Minimize() = 0;

    FunctionData GetFunc() const {
        return Func;
    }

    uint64_t IterCounter = 0;

protected:
    FunctionData Func;
    Vector CurrentX;
    Vector P;
    long double Tau;
};

class TMarkvardFirst : public IMarkvardMethod {
public:
    explicit TMarkvardFirst(FunctionData f, Vector startX)
        : IMarkvardMethod(std::move(f), std::move(startX), 100) {
    }

    Vector Minimize() override {
        while (true) {
            while (true) {
                ++IterCounter;
                auto H = Func.HessianApplier(CurrentX);
                H = OneMatrix(CurrentX.size()) * Tau + H;
                auto g = Func.GradApplier(CurrentX) * -1;
                if (P.size() == 0) {
                    P = Vector(CurrentX.size());
                }
                ConjugateSolve(H, g, EPS, P);
                auto y = CurrentX + P;
                PrevX = CurrentX;
                if (Func.FuncApplier(y) > Func.FuncApplier(CurrentX)) {
                    Tau /= 0.5;
                    continue;
                }
                CurrentX = y;
                Tau *= 0.5;
                break;
            }
            if (P.Norm() < EPS) {
                break;
            }
        }
        return CurrentX;
    }

private:
    Vector PrevX;
};