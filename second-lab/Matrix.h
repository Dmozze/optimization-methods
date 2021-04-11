#pragma once
#include <vector>
#include "Vector.h"

class Matrix {

    using T = long double;
    using Matrix_type = std::vector<Vector>;

    Matrix_type matrix;

public:

    Matrix(size_t n);

    Matrix(Matrix_type &matrix);

    Matrix(std::vector<std::vector<long double>> &matrix_of_vectors);

    size_t size();

    Vector& operator[](size_t index);

    Matrix operator + (Matrix &a);

    Matrix operator - ();

    Matrix operator - (Matrix &matrix1);

    Matrix operator * (T value);

    Vector operator * (Vector &vector);

    Matrix operator * (Matrix &matrix1);

    Matrix transpose();

    T determinant();

    // size <= size()!!!!!
    Matrix angle_matrix(size_t size);

    T main_minor(size_t size);

    bool is_positive_definite_matrix();

};


