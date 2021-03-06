#pragma once
#include <vector>
#include <algebra/Vector.h>
#include <algebra/Matrix.h>

class MatrixProfileFormat {
protected:
    using T = long double;
    using AL = std::vector<T>;
    using AU = AL;
    using Profile = std::vector<int>;
    using Diag = AL;

    T zero = 0.0L;
    Profile profile{};

private:
    AL al{};
    AU au{};
    Diag diag;

    template <typename AL_OR_AU>
    MatrixProfileFormat::T get_el_in_matrix(size_t i, size_t j, AL_OR_AU& al_or_au) const;

    template <typename Type>
    Type mul_vec(Type const& vec, T value) const {
        Type newVec = vec;
        for (auto& i : newVec) {
            i *= value;
        }
        return newVec;
    }

    template <typename AL_OR_AU>
    void set_value_in_matrix(size_t i, size_t j, AL_OR_AU& al_or_au, T value);

    MatrixProfileFormat toProfileFormat(Matrix matrix);

public:
    MatrixProfileFormat(AL al, AU au, Diag diag, Profile profile);

    explicit MatrixProfileFormat(Matrix matrix);

    size_t dim() const;

    T operator()(size_t i, size_t j) const;

    void set(size_t i, size_t j, T value);

    int number_of_elements(size_t i);

    MatrixProfileFormat operator+(MatrixProfileFormat& a);

    MatrixProfileFormat operator-();

    MatrixProfileFormat operator-(MatrixProfileFormat& matrix1);

    MatrixProfileFormat operator*(T value) const;

    Vector operator*(Vector const& vector) const;

    std::vector<long double> operator*(std::vector<long double> const& vector) const;
};
