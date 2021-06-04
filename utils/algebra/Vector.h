#pragma once

#include <vector>
#include <ostream>

class Matrix;

class Vector {
    using T = long double;
    using Vector_type = std::vector<T>;

    Vector_type v;

public:
    Vector() = default;

    Vector(std::initializer_list<T> list)
        : v(list) {
    }

    Vector(size_t n);

    Vector(Vector_type vec);

    size_t size() const;

    T const& operator[](size_t index) const;

    T& operator[](size_t index);

    Vector operator+(Vector const& vector) const;

    Vector& operator+=(Vector const& vector) {
        *this = *this + vector;
        return *this;
    }

    Vector operator-() const;

    Vector operator-(Vector const& vector) const;

    T operator*(Vector const& vector) const;

    Vector operator*(T value) const;

    Vector_type const& data() const {
        return v;
    }

    T Norm();

    friend std::ostream& operator<<(std::ostream& out, Vector vector) {
        out << '[';
        for (size_t i = 0; i < vector.size(); i++) {
            out << vector[i];
            if (i != vector.size() - 1) {
                out << ", ";
            }
        }
        out << ']';
        return out;
    }
};
