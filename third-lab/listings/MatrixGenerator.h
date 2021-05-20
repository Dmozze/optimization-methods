#include <random>
#include <fstream>
#include <vector>
#include <string>
#include "MatrixGenerator.h"
#pragma once

inline constexpr size_t NUMBER_OF_TESTS = 20;
inline constexpr size_t SIZE = 20;
inline constexpr long double DENSITY = 1; // SIZE * 1 / (2 * density) cells will fill up

void write_vec_to_file(const std::string& file_name, const std::vector<long double>& output);

void write_matrix_to_file(const std::string& file_name, const std::vector<std::vector<long double>> &output);

std::vector<long double> generate_ia(size_t matrix_size = SIZE);

std::vector<long double> fill_up(size_t vec_size);

void gen_test(size_t number_of_test, size_t n = SIZE);

void generate_tests();

void generate_tests_gauss();


namespace {
    std::default_random_engine e1(42);
    std::uniform_int_distribution<uint32_t> uniform_dist_int(0, SIZE);
    std::uniform_int_distribution<int32_t> uniform_dist_value(-4, 0);
    std::uniform_int_distribution<int32_t> uniform_dist_gauss_value(-10, 10);
} // namespace


void write_vec_to_file(const std::string& file_name, const std::vector<long double>& output) {
    std::ofstream out(file_name);
    for (long double i : output) {
        out << i << " ";
    }
    out.close();
}

void write_matrix_to_file(const std::string& file_name, const std::vector<std::vector<long double>> &output) {
    std::ofstream out(file_name);
    for (auto &vec : output) {
        for (auto el : vec) {
            out << el << " ";
        }
        out << std::endl;
    }
    out.close();
}

std::vector<long double> generate_ia(size_t matrix_size) {
    std::vector<long double> result(matrix_size + 1, 0);
    for (size_t i = 2; i < result.size(); i++) {
        result[i] = static_cast<uint32_t>(uniform_dist_int(e1) * DENSITY) % (i + 1);
    }
    for (size_t i = 1; i < result.size(); i++) {
        result[i] += result[i - 1];
    }
    return result;
}

std::vector<std::vector<long double>> generate_gauss_matrix(size_t matrix_size) {
    std::vector<std::vector<long double>> result(matrix_size, std::vector<long double>(matrix_size));
    for (size_t i = 0; i < matrix_size; i++) {
        for (size_t j = 0; j < matrix_size; j++) {
            result[i][j] = uniform_dist_gauss_value(e1);
        }
    }
    for (size_t i = 0; i < matrix_size; i++) {
        if (result[i][i] == 0) {
            result[i][i]++;
        }
    }
    return result;
}

std::vector<long double> fill_up(size_t vec_size) {
    std::vector<long double> result(vec_size + 1);
    for (long double& i : result) {
        i = uniform_dist_value(e1);
    }
    result[0] = 0.0L;
    return result;
}

void gen_test(size_t number_of_test, size_t n) {
    std::vector<long double> ai = generate_ia(n);
    std::vector<long double> di = fill_up(n);
    size_t size_for_triangles = static_cast<int32_t>(ai.back());
    std::vector<long double> al = fill_up(size_for_triangles);
    std::vector<long double> au = fill_up(size_for_triangles);
    std::string result_name = "tests/profile/test_" + std::to_string(number_of_test);
    write_vec_to_file(result_name + "di" + ".txt", di);
    write_vec_to_file(result_name + "al" + ".txt", al);
    write_vec_to_file(result_name + "au" + ".txt", au);
    write_vec_to_file(result_name + "ai" + ".txt", ai);
}

void gen_test_gauss(size_t n) {
    write_matrix_to_file("tests/gauss/" + std::to_string(n) + ".txt", generate_gauss_matrix(n));
}


void generate_tests_gauss() {
    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
        gen_test_gauss(50 * i);
    }
}

void generate_tests() {
    for (size_t i = 1; i <= NUMBER_OF_TESTS; i++) {
        gen_test(i, i * 50);
    }
}

