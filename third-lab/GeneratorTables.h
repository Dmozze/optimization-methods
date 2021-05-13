#pragma once

#include "MatrixProfileFormat.h"
#include "LUSolver.h"
#include "LUMatrix.h"
#include <string>
#include <fstream>
#include <vector>


#define DIR "tests/profile/"
#define TEST "test_"
#define AL "al"
#define AU "au"
#define AI "ai"
#define TXT ".txt"

inline Vector get_iota_vector(size_t n) {
    Vector iota(n);
    iota[0] = 1;
    for (size_t i = 1; i < n; i++) {
        iota[i] = iota[i - 1] + 1;
    }
    return iota;
}

template<typename T>
inline std::vector<T> read_vec(string &file_name) {
    std::ifstream stream(file_name);
    std::vector<T> answer;
    T el;
    while (stream >> el) {
        answer.push_back(el);
    }
    return answer;
}

inline string get_file_name(int i, string &type) {
    return DIR + TEST + std::to_string(i) + type + TXT;
}

template<typename T>
inline void calculate_diag_elements(MatrixProfileFormat &matrix, int k) {
    for (size_t i = 1; i <= matrix.dim(); i++) {
        T res = 0;
        for (size_t j = 1; j <= matrix.dim(); j++) {
            if (i != j) {
                res -= matrix(i, j);
            }
        }
        matrix.set(i, i, res);
    }
    matrix.set(1, 1, matrix(1, 1) + std::powl(10.0L, -k));
}

template<typename T>
inline vector<T> generate_f(MatrixProfileFormat &matrix) {
    std::vector<T> iota_vec(matrix.dim());
    std::iota(iota_vec.begin(), iota_vec.end(), 1.0L);
    return matrix * iota_vec;
}


inline void generate_problem_and_solve(int i,) {
    using T = long double;
    using VT = std::vector<T>;
    std::vector<int> profile = read_vec(get_file_name(i, AI));
    VT al = read_vec(get_file_name(i, AL));
    VT au = read_vec(get_file_name(i, AU));

    VT diag(profile.size() - 1, 0);

    MatrixProfileFormat matrix(al, au, diag, profile);

    calculate_diag_elements<T>(matrix);

    VT f = generate_f<T>(matrix);

}

inline void put_result_to_table(int k, LUMatrix matrix, Vector f, std::ofstream& table_stream) {
    Vector x = LUSolve(std::move(matrix), std::move(f));
    Vector iota = get_iota_vector(n);

    long double norma = x.norma();
    long double norma_difference = (iota - x).norma();

    table_stream << matrix.dim() << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << endl;
}


