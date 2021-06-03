#include <cmath>
#include <utility>
#include "Vector.h"

Vector::Vector(size_t n) {
    v.assign(n, 0.0L);
}

Vector::Vector(Vector_type vec)
    : v(std::move(vec)) {
}

size_t Vector::size() const {
    return v.size();
}

Vector::T const& Vector::operator[](size_t index) const {
    return v[index];
}

Vector::T& Vector::operator[](size_t index) {
    return v[index];
}

Vector Vector::operator+(Vector const& vector) const {
    Vector_type sum_v(std::max(v.size(), vector.size()));
    for (size_t i = 0; i < sum_v.size(); i++) {
        sum_v[i] = v[i] + vector[i];
    }
    return Vector(sum_v);
}

Vector::T Vector::operator*(Vector const& vector) const {
    T scalar_prod = 0.0L;
    for (size_t i = 0; i < std::min(v.size(), vector.size()); i++) {
        scalar_prod += v[i] * vector[i];
    }
    return scalar_prod;
}

Vector Vector::operator-() {
    Vector_type neg(v.size());
    for (size_t i = 0; i < neg.size(); i++) {
        neg[i] = -v[i];
    }
    return Vector(neg);
}

Vector Vector::operator-(Vector& vector) {
    Vector this_(this->v);
    Vector neg_vec(-vector);
    return this_ + neg_vec;
}

Vector Vector::operator*(Vector::T value) const {
    Vector_type answer(size());
    for (size_t i = 0; i < answer.size(); i++) {
        answer[i] = this->operator[](i) * value;
    }
    return Vector(answer);
}

Vector::T Vector::Norm() {
    Vector this_(v);
    T square_norma = this_ * this_;
    return sqrtl(square_norma);
}

Matrix Vector::operator%(const Vector &vector) const {
    Matrix answer(vector.size());
    for (size_t i = 0; i < vector.size(); i++) {
        for (size_t j = 0; j < vector.size(); j++) {
            answer[i][j] = vector[i] * vector[j];
        }
    }
    return answer;
}
