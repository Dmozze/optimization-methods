#pragma once
#include <vector>
#include "Vector.h"

class Matrix {
    using T = long double;
    using Matrix_type = std::vector<Vector>;

    Matrix_type matrix;

public:
    Matrix() = default;
    
    Matrix(size_t n);

    Matrix(Matrix_type const& matrix);

    Matrix(std::vector<std::vector<long double>> matrix_of_vectors);

    Matrix(std::initializer_list<std::initializer_list<long double>> list) {
        for (auto&& inside_list : list) {
            matrix.emplace_back(inside_list);
        }
    }

    size_t size() const;

    Vector& operator[](size_t index);

    Vector const& operator[](size_t index) const;

    Matrix operator+(Matrix& a);

    Matrix operator-() const;

    Matrix operator-(Matrix const& matrix1) const;

    Matrix operator*(T value);

    Vector operator*(Vector const& vector) const;

    Matrix operator*(Matrix& matrix1);

    Matrix transpose();

    T determinant();

    // size <= size()!!!!!
    Matrix angle_matrix(size_t size);

    T main_minor(size_t size);

    bool is_positive_definite_matrix();
};
