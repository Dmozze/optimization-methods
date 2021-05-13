#pragma once
#include <vector>
#include <ostream>

class Vector {
    using T = long double;
    using Vector_type = std::vector<T>;

    Vector_type v;

public:
    Vector(size_t n);

    Vector(Vector_type vec);

    size_t size() const;

    T const& operator[](size_t index) const;
    T& operator[](size_t index);

    Vector operator+(Vector& vector);

    Vector operator-();

    Vector operator-(Vector& vector);

    T operator*(Vector& vector);

    Vector operator*(T value);

    T norma();

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
