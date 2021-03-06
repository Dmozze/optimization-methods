#include "Matrix.h"
#include <iostream>

Matrix::Matrix(size_t n) {
    matrix.assign(n, Vector(n));
}

Matrix::Matrix(Matrix::Matrix_type const& matrix)
    : matrix(matrix) {
}

size_t Matrix::size() const {
    return matrix.size();
}

Vector& Matrix::operator[](size_t index) {
    return matrix[index];
}

Vector const& Matrix::operator[](size_t index) const {
    return matrix[index];
}

Matrix Matrix::operator+(Matrix& a) {
    Matrix_type sum(size(), Vector(size()));
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            sum[i][j] = this->operator[](i)[j] + a[i][j];
        }
    }
    return Matrix(sum);
}

Matrix Matrix::operator-() const {
    Matrix_type neg(size(), Vector(size()));
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            neg[i][j] = -this->operator[](i)[j];
        }
    }
    return Matrix(neg);
}

Matrix Matrix::operator-(Matrix const& matrix1) const {
    Matrix this_(this->matrix);
    Matrix neg = -matrix1;
    return this_ + neg;
}

Matrix Matrix::operator*(Matrix::T value) {
    Matrix_type matrixProd(size(), Vector(size()));
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            matrixProd[i][j] = this->operator[](i)[j] * value;
        }
    }
    return Matrix(matrixProd);
}

Vector Matrix::operator*(Vector const& vector) const {
    Vector answer(size());
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            answer[i] += this->operator[](j)[i] * vector[j];
        }
    }
    return answer;
}

Matrix Matrix::operator*(Matrix& matrix1) {
    Matrix_type prod(size(), Vector(size()));
    Matrix this_(this->matrix);
    for (size_t i = 0; i < size(); i++) {
        prod[i] = this_ * matrix1[i];
    }
    return Matrix(prod);
}

Matrix Matrix::transpose() {
    Matrix_type transposeMatrix(size(), Vector(size()));
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            transposeMatrix[i][j] = this->operator[](j)[i];
        }
    }
    return Matrix(transposeMatrix);
}

Matrix::T Matrix::determinant() {
    Matrix this_(matrix);

    for (size_t k = 0; k < size() - 1; k++) {
        for (size_t i = k + 1; i < size(); i++) {
            T tmp = -this_[i][k] / this_[k][k];
            for (size_t j = 0; j < size(); j++) {
                this_[i][j] += this_[k][j] * tmp;
            }
        }
    }

    T d = 1;
    for (size_t i = 0; i < size(); i++) {
        d *= this_[i][i];
    }
    return d;
}

Matrix Matrix::angle_matrix(size_t size) {
    Matrix_type angle(size, Vector(size));
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            angle[i][j] = this->operator[](i)[j];
        }
    }
    return Matrix(angle);
}

Matrix::T Matrix::main_minor(size_t size) {
    return angle_matrix(size).determinant();
}

bool Matrix::is_positive_definite_matrix() {
    bool f = true;
    for (size_t i = 0; i < size(); i++) {
        if (main_minor(i + 1) <= 0.0L) {
            f = false;
            break;
        }
    }
    return f;
}

Matrix::Matrix(std::vector<std::vector<long double>> matrix_of_vectors) {
    for (auto&& vec : matrix_of_vectors) {
        matrix.emplace_back(std::move(vec));
    }
}