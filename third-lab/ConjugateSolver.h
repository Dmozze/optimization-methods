#pragma once
#include <algebra/Vector.h>
#include "MatrixSparseFormat.h"


inline int ConjugateSolve(MatrixSparseFormat const & A, Vector f, long double epsilon, Vector &x) {
    Vector A_x = A * x;
    Vector r = f - A_x;
    Vector z = r;
    int cnt = 0;
//    bool flag = false;
    while (true) {
//        if (cnt ==  100) {
//            break;
//        }
//        std::cout << "x: " << x << std::endl;
//        std::cout << "r: " << r << std::endl;
//        std::cout << "z: " << z << std::endl;
//        std::cout << std::endl;
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
//        if (flag) {
//            break;
//        }
        if (r.norma()  < epsilon) {
            break;
        }
    }
    return cnt;
}