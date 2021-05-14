#pragma once

#include "MatrixProfileFormat.h"
#include "LUSolver.h"
#include "LUMatrix.h"
#include <string>
#include <fstream>
#include <vector>
#include "MatrixGenerator.h"
#include <cmath>
#include <iomanip>
// todo: insert absolute path on your system
static const std::string DIR = "tests/profile/";
static const std::string TEST = "test_";
static const std::string AL = "al";
static const std::string AU = "au";
static const std::string AI = "ai";
static const std::string TXT = ".txt";

inline Vector get_iota_vector(size_t n) {
    Vector iota(n);
    iota[0] = 1;
    for (size_t i = 1; i < n; i++) {
        iota[i] = iota[i - 1] + 1;
    }
    return iota;
}

template <typename T>
inline std::vector<T> read_vec(std::string const& file_name) {
    std::ifstream stream(file_name);
    std::vector<T> answer;
    T el;
    while (stream >> el) {
        answer.push_back(el);
    }
    stream.close();
    return answer;
}

inline std::string get_file_name(int i, std::string const& type) {
    return DIR + TEST + std::to_string(i) + type + TXT;
}

template <typename T>
inline void calculate_diag_elements(MatrixProfileFormat& matrix, int k) {
    for (size_t i = 1; i <= matrix.dim(); i++) {
        T res = 0;
        for (size_t j = 1; j <= matrix.dim(); j++) {
            if (i != j) {
                res -= matrix(i, j);
            }
        }
        if (res == 0) {
            res++;
        }
        matrix.set(i, i, res);
    }
    matrix.set(1, 1, matrix(1, 1) + powl(10.0L, -k));
}

template <typename T>
inline std::vector<T> generate_f(MatrixProfileFormat& matrix) {
    std::vector<T> iota_vec(matrix.dim());
    std::iota(iota_vec.begin(), iota_vec.end(), 1.0L);
    return matrix * iota_vec;
}

inline void put_result_to_table(int k, LUMatrix const& matrix, Vector f, std::ofstream& table_stream) {
    Vector x = LUSolve(matrix, std::move(f));
    Vector iota = get_iota_vector(matrix.dim());

    long double norma = iota.norma();
    long double norma_difference = (iota - x).norma();
    std::cout << std::setprecision(8);
    table_stream << std::setprecision(8);
    std::cout << matrix.dim() << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
    table_stream << matrix.dim() << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
}

inline void invert_problem(MatrixProfileFormat &matrix) {
    for (int i = 1; i <= matrix.dim(); i++) {
        for (int j = 1; j <= matrix.dim(); j++) {
            if (i != j) {
                matrix.set(i, j, -matrix(i, j));
            }
        }
    }
}

inline void generate_problem_and_solve(int i, int k, std::ofstream &table_stream, bool invert) {
    using T = long double;
    using VT = std::vector<T>;
    std::vector<int> profile = read_vec<int>(get_file_name(i, AI));
    VT al = read_vec<long double>(get_file_name(i, AL));
    VT au = read_vec<long double>(get_file_name(i, AU));

    VT diag(profile.size() - 1, 0);

    MatrixProfileFormat matrix(al, au, diag, profile);

    calculate_diag_elements<T>(matrix, k);

    if (invert) {
        invert_problem(matrix);
    }

    VT f = generate_f<T>(matrix);

    LUMatrix matrix_lu(matrix);

    put_result_to_table(k, matrix_lu, f, table_stream);
}

inline void run_tests_for_generate_problems() {
    std::ofstream table_stream("tables/lu/table.csv");
    for (int i = 1; i <= NUMBER_OF_TESTS; i++) {
        for (int k = 1; k <= 7; k++) {
            generate_problem_and_solve(i, k, table_stream, false);
        }
    }
    table_stream.close();
}

inline void run_tests_for_generate_problems_invert() {
    std::ofstream table_stream_invert("tables/lu/table_invert.csv");
    for (int i = 1; i <= NUMBER_OF_TESTS; i++) {
        for (int k = 1; k <= 7; k++) {
            generate_problem_and_solve(i, k, table_stream_invert, true);
        }
    }
}
