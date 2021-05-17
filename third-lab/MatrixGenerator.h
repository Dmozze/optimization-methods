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