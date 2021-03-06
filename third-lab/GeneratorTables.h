#pragma once

#include "MatrixProfileFormat.h"
#include "LUSolver.h"
#include "LUMatrix.h"
#include <string>
#include <fstream>
#include <vector>
#include "MatrixGenerator.h"
#include "MatrixSparseFormat.h"
#include "ConjugateSolver.h"
#include <cmath>
#include <iomanip>

static const std::string DIR_PROFILE = "tests/profile/";
static const std::string DIR_GAUSS = "tests/gauss/";
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

template <typename T>
inline Matrix read_matrix(std::string const& file_name, size_t n) {
    std::ifstream stream(file_name);
    std::vector<std::vector<T>> answer(n, std::vector<T>(n));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            stream >> answer[i][j];
        }
    }
    stream.close();
    return Matrix(answer);
}

inline std::string get_file_name(int i, std::string const& type) {
    return DIR_PROFILE + TEST + std::to_string(i) + type + TXT;
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
inline std::vector<T> generate_f(const MatrixProfileFormat& matrix) {
    std::vector<T> iota_vec(matrix.dim());
    std::iota(iota_vec.begin(), iota_vec.end(), 1.0L);
    return matrix * iota_vec;
}

template <typename T>
inline Vector generate_f(Matrix& matrix) {
    std::vector<T> iota_vec(matrix.size());
    std::iota(iota_vec.begin(), iota_vec.end(), 1.0L);
    Vector iota(iota_vec);
    return matrix * iota;
}

inline void put_result_to_table_lu_solve(int k, LUMatrix const& matrix, Vector f, std::ofstream& table_stream) {
    Vector x = LUSolve(matrix, std::move(f));
    Vector iota = get_iota_vector(matrix.dim());

    long double norma = iota.Norm();
    long double norma_difference = (iota - x).Norm();
    std::cout << std::setprecision(8);
    table_stream << std::setprecision(8);
    std::cout << matrix.dim() << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
    table_stream << matrix.dim() << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
}

inline void put_result_to_table_gauss_solve(Matrix matrix, Vector f, std::ofstream& table_stream) {
    Vector iota = get_iota_vector(matrix.size());
    Vector x = GaussSolve(matrix, std::move(f));
    long double norma = iota.Norm();
    long double norma_difference = (iota - x).Norm();
    std::cout << std::setprecision(8);
    table_stream << std::setprecision(8);
    std::cout << matrix.size() << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
    table_stream << matrix.size() << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
}

inline void put_result_to_table_gauss_solve_with_k(Matrix matrix, Vector f, int k, std::ofstream& table_stream) {
    Vector iota = get_iota_vector(matrix.size());
    Vector x = GaussSolve(matrix, std::move(f));
    long double norma = iota.Norm();
    long double norma_difference = (iota - x).Norm();
    std::cout << std::setprecision(8);
    table_stream << std::setprecision(8);
    std::cout << matrix.size() << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
    table_stream << matrix.size() << ";" << k << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
}

inline void put_result_to_table(LUMatrix const& matrix, Vector f, std::ofstream& table_stream) {
    Vector x = LUSolve(matrix, std::move(f));
    Vector iota = get_iota_vector(matrix.dim());

    long double norma = iota.Norm();
    long double norma_difference = (iota - x).Norm();
    std::cout << std::setprecision(8);
    table_stream << std::setprecision(8);
    std::cout << matrix.dim() << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
    table_stream << matrix.dim() << ";" << norma_difference << ";" << norma_difference / norma << std::endl;
}

inline void invert_problem(MatrixProfileFormat& matrix) {
    for (int i = 1; i <= matrix.dim(); i++) {
        for (int j = 1; j <= matrix.dim(); j++) {
            if (i != j) {
                matrix.set(i, j, -matrix(i, j));
            }
        }
    }
}

using T = long double;
using VT = std::vector<T>;

inline void generate_f_and_put_res(int k, std::ofstream& table_stream, const MatrixProfileFormat& matrix) {
    VT f = generate_f<T>(matrix);

    LUMatrix matrix_lu(matrix);

    put_result_to_table_lu_solve(k, matrix_lu, f, table_stream);
}

inline void generate_f_and_put_res(std::ofstream& table_stream, const MatrixProfileFormat& matrix) {
    VT f = generate_f<T>(matrix);

    LUMatrix matrix_lu(matrix);

    put_result_to_table(matrix_lu, f, table_stream);
}

inline void generate_problem_lu_format_and_solve(int i, int k, std::ofstream& table_stream, bool invert) {
    std::vector<int> profile = read_vec<int>(get_file_name(i, AI));
    VT al = read_vec<long double>(get_file_name(i, AL));
    VT au = read_vec<long double>(get_file_name(i, AU));

    VT diag(profile.size() - 1, 0);

    MatrixProfileFormat matrix(al, au, diag, profile);

    calculate_diag_elements<T>(matrix, k);

    if (invert) {
        invert_problem(matrix);
    }

    generate_f_and_put_res(k, table_stream, matrix);
}

inline void generate_problem_gauss_same_as_lu_format_and_solve(int test_number, int k, std::ofstream& table_stream) {
    std::vector<int> profile = read_vec<int>(get_file_name(test_number, AI));
    VT al = read_vec<long double>(get_file_name(test_number, AL));
    VT au = read_vec<long double>(get_file_name(test_number, AU));

    VT diag(profile.size() - 1, 0);

    MatrixProfileFormat matrix(al, au, diag, profile);
    calculate_diag_elements<T>(matrix, k);
    std::vector<std::vector<long double>> converted_matrix(matrix.dim());
    for (size_t i = 0; i != matrix.dim(); ++i) {
        converted_matrix[i].resize(matrix.dim());
        for (size_t j = 0; j != matrix.dim(); ++j) {
            converted_matrix[i][j] = matrix(i + 1, j + 1);
        }
    }
    Vector f = generate_f<T>(matrix);
    put_result_to_table_gauss_solve_with_k(converted_matrix, f, k, table_stream);
}

inline void generate_problem_gauss_format_and_solve(size_t n, std::ofstream& table_stream) {
    Matrix matrix = read_matrix<T>(DIR_GAUSS + std::to_string(n) + TXT, n);
    Vector f = generate_f<T>(matrix);

    put_result_to_table_gauss_solve(matrix, f, table_stream);
}

inline void run_tests_lu() {
    std::ofstream table_stream("tex/lu/table.csv");
    table_stream << "$n$;$k$;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$" << std::endl;
    for (size_t i : {1, 4, 10, 14, 20}) {
        for (int k = 1; k <= 7; k++) {
            generate_problem_lu_format_and_solve(i, k, table_stream, false);
        }
    }
    table_stream.close();
}

inline void run_tests_gauss_same_as_lu() {
    std::ofstream table_stream("tex/gauss/table.csv");
    table_stream << "$n$;$k$;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$" << std::endl;
    for (size_t i : {1, 4, 10, 14, 20}) {
        for (int k = 1; k <= 7; k++) {
            generate_problem_gauss_same_as_lu_format_and_solve(i, k, table_stream);
        }
    }
    table_stream.close();
}

inline void run_tests_gauss() {
    std::ofstream table_stream("tex/gauss/table.csv");
    table_stream << "$n$;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$" << std::endl;
    for (size_t i : {1, 4, 10, 14, 20}) {
        generate_problem_gauss_format_and_solve(i * 50, table_stream);
    }
    table_stream.close();
}

inline void run_tests_for_generate_problems_invert() {
    std::ofstream table_stream_invert("tex/lu/table_invert.csv");
    table_stream_invert << "$n$;$k$;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$" << std::endl;
    for (size_t i : {1, 4, 10, 14, 20}) {
        for (int k = 1; k <= 7; k++) {
            generate_problem_lu_format_and_solve(i, k, table_stream_invert, true);
        }
    }
    table_stream_invert.close();
}

inline void run_tests_for_hilbert_matrix() {
    std::ofstream table_stream_hilbert("tex/lu/table_hilbert.csv");
    table_stream_hilbert << "$n$;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$" << std::endl;
    for (size_t i : {1, 4, 10, 14, 20}) {
        MatrixProfileFormat matrix = hilbert_matrix_generator_profile_format(50 * i);
        generate_f_and_put_res(table_stream_hilbert, matrix);
    }
    table_stream_hilbert.close();
}

inline void run_tests_for_hilbert_matrix_gauss() {
    std::ofstream table_stream_hilbert("tex/gauss/table_hilbert.csv");
    table_stream_hilbert << "$n$;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$" << std::endl;
    for (size_t I : {1, 4, 10, 14, 20}) {
        MatrixProfileFormat matrix = hilbert_matrix_generator_profile_format(I * 50);
        std::vector<std::vector<long double>> converted_matrix(matrix.dim());
        for (size_t i = 0; i != matrix.dim(); ++i) {
            converted_matrix[i].resize(matrix.dim());
            for (size_t j = 0; j != matrix.dim(); ++j) {
                converted_matrix[i][j] = matrix(i + 1, j + 1);
            }
        }
        Vector f = generate_f<T>(matrix);
        put_result_to_table_gauss_solve(converted_matrix, f, table_stream_hilbert);
    }
    table_stream_hilbert.close();
}

template <typename T>
void calculate_diag(MatrixSparseFormat& matrix) {
    for (size_t i = 1; i <= matrix.dim(); i++) {
        for (size_t j = 1; j <= matrix.dim(); j++) {
            matrix.set_diag_element(i, matrix(i, i) - matrix(i, j));
        }
    }
    matrix.set_diag_element(1, matrix(1, 1) + 1);
}

template <typename T>
MatrixSparseFormat read_sparse_matrix(size_t n, size_t density) {
    const std::string dir = "tests/conjugate/" + std::to_string(n) + "_" + std::to_string(density);
    std::vector<T> alu = read_vec<T>(dir + "alu.txt");
    std::vector<size_t> indexes = read_vec<size_t>(dir + "indexes.txt");
    std::vector<int> profile = read_vec<int>(dir + "profile.txt");
    std::vector<T> diag(n, 0);
    MatrixSparseFormat answer(alu, diag, profile, indexes);
    calculate_diag<T>(answer);
    return answer;
}

Vector get_x_star(size_t n) {
    std::vector<long double> iot(n);
    std::iota(iot.begin(), iot.end(), 1);
    Vector ans(iot);
    return ans;
}

Vector gen_f_conjugate(MatrixSparseFormat& matrix) {
    return matrix * get_x_star(matrix.dim());
}

void solve_problem_conjugate(size_t n, size_t density, std::ofstream& table_stream) {
    MatrixSparseFormat matrixSparseFormat = read_sparse_matrix<long double>(n, density);
    Vector f = gen_f_conjugate(matrixSparseFormat);
    Vector x0(n);
    long double epsilon = 1e-7;
    int cnt = ConjugateSolve(matrixSparseFormat, f, epsilon, x0);
    Vector x_star = get_x_star(n);
    Vector diff_x_star_xk = x0 - x_star;
    Vector Ax = matrixSparseFormat * x0;
    Vector diff_f_Ax = f - Ax;
    auto diff_x_star_xk_norma = diff_x_star_xk.Norm();
    auto x_star_norma = x_star.Norm();
    auto diff_div1 = diff_x_star_xk_norma / x_star_norma;
    auto diff_div2 = diff_f_Ax.Norm() / f.Norm();
    std::cerr << "n: " << n << " x* norm: " << x_star_norma << " diff_div2: " << diff_div2 << std::endl;
    table_stream << n << ";"
                 << cnt << ";"
                 << diff_x_star_xk_norma << ";"
                 << diff_div1 << ";"
                 << diff_div1 / diff_div2
                 << std::endl;
    if (x0.size() <= 100) {
        std::cout << x0 << std::endl;
    }
}

void run_tests_conjugate() {
    std::ofstream table_stream("tex/conjugate/table.csv");
    table_stream << "$n$;Количество итераций;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$;$cond(A)$";
    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
        //        gen_conjugate_test(50 * i, 100 * i);
        solve_problem_conjugate(50 * i, 100 * i, table_stream);
    }
    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
        //        gen_conjugate_test(500 * i, 1000 * i);
        solve_problem_conjugate(500 * i, 1000 * i, table_stream);
    }
    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
        //        gen_conjugate_test(5000 * i, 100000 * i);
        solve_problem_conjugate(5000 * i, 100000 * i, table_stream);
    }
}

//void run_hilbert_tests_conjugate() {
//    std::ofstream table_stream("tex/conjugate/table_hilbert.csv");
//    table_stream << "$n$;Количество итераций;$||x_k - x^*||$;$||x_k - x^*||/||x^*||$;$cond(A)$";
//    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
//        //        gen_conjugate_test(50 * i, 100 * i);
//        solve_problem_conjugate(50 * i, 100 * i, table_stream);
//    }
//    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
//        //        gen_conjugate_test(500 * i, 1000 * i);
//    }
//    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
//        //        gen_conjugate_test(5000 * i, 100000 * i);
//    }
//}
