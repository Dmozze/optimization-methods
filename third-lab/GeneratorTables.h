#pragma once

#include "MatrixProfileFormat.h"
#include "LUSolver.h"
#include "LUMatrix.h"
#include <string>
#include <fstream>

inline Vector get_iota_vector(size_t n) {
    Vector iota(n);
    iota[0] = 1;
    for (size_t i = 1; i < n; i++) {
        iota[i] = iota[i - 1] + 1;
    }
    return iota;
}




inline void put_result_to_table(int n, int k, LUMatrix matrix, Vector f, std::ofstream& table_stream) {
    Vector x = LUSolve(std::move(matrix), std::move(f));
    Vector iota = get_iota_vector(n);

    long double norma = x.norma();
    long double norma_difference = (iota - x).norma();

    table_stream << n << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << endl;
}
