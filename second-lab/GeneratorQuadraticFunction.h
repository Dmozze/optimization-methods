#pragma once
#include <algebra/Vector.h>
#include <random>
#include "DiagonalQuadraticFunction.h"

class GeneratorQuadraticFunction {
    using T = long double;
    std::mt19937 generator;

public:
    GeneratorQuadraticFunction() {
        std::random_device rd;
        std::mt19937 ge(rd());
        generator = ge;
    }
    std::vector<T> gen_quad(size_t n, T k);
    Vector generateVector(size_t n) {
        std::uniform_real_distribution<T> unif_normal(1.0L, 1000.0L);
        return Vector(gen_quad(n, unif_normal(generator)));
    }

    DiagonalQuadraticFunction gen_diag_quad(size_t n, T k) {
        std::vector<T> gen = gen_quad(n, k);
        Vector vec(gen);
        DiagonalMatrix diagonalMatrix(vec);
        Vector g = generateVector(n);
        return DiagonalQuadraticFunction(diagonalMatrix, g, 0.0L);
    }
};
