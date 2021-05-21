#pragma once
#include <algebra/Vector.h>
#include "MatrixSparseFormat.h"


inline int ConjugateSolve(MatrixSparseFormat A, Vector f, long double epsilon, Vector &x) {
    Vector A_x = A * x;
    Vector r = f - A_x;
    Vector z = r;
    int cnt = 0;
    while (true) {
        if (r.norma() < epsilon * f.norma()) {
            break;
        }
        cnt++;
        Vector A_z = A * z;
        long double r_square = r * r;
        long double alpha = r_square / (A_z * z);
        auto alpha_z = z * alpha;
        x = x + alpha_z;
        auto alpha_A_z = A_z * alpha;
        r = r - alpha_A_z;
        long double betta = (r * r) / r_square;
        auto betta_z = z * betta;
        z = r + betta_z;
    }
    return cnt;
}