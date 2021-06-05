#pragma once
#include <algebra/Vector.h>
#include "MatrixSparseFormat.h"

template<typename MatrixFormat>
inline int ConjugateSolve(MatrixFormat const & A, Vector f, long double epsilon, Vector &x) {
    Vector A_x = A * x;
    Vector r = f - A_x;
    Vector z = r;
    int cnt = 0;
    while (true) {
        cnt++;
        auto A_z = A * z;
        auto Az_z = A_z * z;
        auto r_r = r * r;
        auto alpha = r_r / Az_z;
        auto alpha_z = z * alpha;
        x = x + alpha_z;
        auto alpha_Az = A_z * alpha;
        r = r - alpha_Az;
        auto r1_r1 = r * r;
        auto betta = r1_r1 / r_r;
        auto betta_z = z * betta;
        z = r + betta_z;
        if (r.Norm()  < epsilon) {
            break;
        }
    }
    return cnt;
}