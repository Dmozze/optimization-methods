#pragma once
#include "Vector.h"
#include <random>
#include "DiagonalQuadraticFunction.h"

class GeneratorQuadraticFunction {
    using T = long double;
    std::mt19937 generator;
public:
    GeneratorQuadraticFunction(){
        std::random_device rd;
        std::mt19937 ge(rd());
        generator = ge;
    }
    std::vector<T> gen_quad(size_t n, T k);
    Vector generateVector(size_t n) {
        return Vector(gen_quad(n, 1000.0L));
    }

    DiagonalQuadraticFunction gen_diag_quad(size_t n, T k) {
        std::vector<T> gen = gen_quad(n, k);
        Vector vec(gen);
        Diagonal_Matrix diagonalMatrix(vec);
        Vector g = generateVector(n);
        return DiagonalQuadraticFunction(diagonalMatrix, g, 0.0L);
    }

};


