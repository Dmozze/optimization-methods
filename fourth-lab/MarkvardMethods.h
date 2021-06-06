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
    static constexpr long double BETA = 0.25;

public:
    explicit TMarkvardFirst(FunctionData f, Vector startX)
        : IMarkvardMethod(std::move(f), std::move(startX), 100000) {
    }

    Vector Minimize() override {
        while (true) {
            ++IterCounter;
            while (true) {
                std::cout << Tau << std::endl;
                auto H = Func.HessianApplier(CurrentX);
                H = OneMatrix(CurrentX.size()) * Tau + H;
                auto g = Func.GradApplier(CurrentX) * -1;
                if (P.size() == 0) {
                    P = Vector(CurrentX.size());
                }
                ConjugateSolve(H, g, EPS, P);
                //  P = GaussSolve(H, g);
                auto y = CurrentX + P;
                PrevX = CurrentX;
                if (Func.FuncApplier(y) > Func.FuncApplier(CurrentX)) {
                    Tau /= BETA;
                    continue;
                }
                CurrentX = y;
                Tau *= BETA;
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

class TMarkvardSecond : public IMarkvardMethod {
    static constexpr long double BETA = 0.25;

public:
    explicit TMarkvardSecond(FunctionData f, Vector startX)
        : IMarkvardMethod(std::move(f), std::move(startX), 10000) {
        P = Vector(CurrentX.size());
    }

    Vector Minimize() override {
        bool finished = false;
        while (!finished) {
            auto savedTau = Tau;
            Vector dx;
            size_t choleskyCnt = 0;
            // std::cout << Tau << std::endl;
            ++IterCounter;
            while (true) {
                if (Func.GradApplier(CurrentX).Norm() < EPS) {
                    break;
                }
                auto taum = OneMatrix(CurrentX.size()) * Tau;
                auto shift = Func.HessianApplier(CurrentX) + taum;
                ++choleskyCnt;
                if (!choleskyCheck(shift)) {
                    Tau = std::max(static_cast<long double>(1), 2 * Tau);
                    continue;
                }
                std::cout << IterCounter << " & " << choleskyCnt << " \\\\ \\hline \n";
                P = Vector(CurrentX.size());
                ConjugateSolve(shift, -Func.GradApplier(CurrentX), EPS, P);
                auto newX = CurrentX + P;

                if (Func.FuncApplier(CurrentX) < Func.FuncApplier(newX)) {
                    Tau /= BETA;
                } else {
                    CurrentX = newX;
                    if (P.Norm() < EPS) {
                        finished = true;
                    }
                    Tau *= BETA;
                    break;
                }
            }
        }
        return CurrentX;
    }

private:
    Vector PrevX;

    static bool choleskyCheck(Matrix A) {
        Matrix L(A.size());
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A.size(); j++) {
                long double sum = 0.0;
                for (int k = 0; k < i; k++) {
                    sum += L[i][k] * L[j][k];
                }
                if (i == j) {
                    if (A[i][i] - sum < 0) {
                        return false;
                    }
                    L[i][i] = std::sqrt(A[i][i] - sum);
                } else {
                    //                    if (std::abs(L[j][j]) < 1e-8) {
                    //                        return {};
                    //                    }
                    L[i][j] = (A[i][j] - sum) / L[j][j];
                }
            }
            if (L[i][i] <= 0) {
                return false;
            }
        }
        return true;
    }
};