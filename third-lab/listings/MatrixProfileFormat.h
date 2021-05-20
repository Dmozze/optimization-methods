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

MatrixProfileFormat::MatrixProfileFormat(AL al, AU au, Diag diag, Profile profile)
    : al(std::move(al))
    , au(std::move(au))
    , profile(std::move(profile))
    , diag(std::move(diag)) {
}

size_t MatrixProfileFormat::dim() const {
    return profile.size() - 1;
}

template <typename AL_OR_AU>
MatrixProfileFormat::T MatrixProfileFormat::get_el_in_matrix(size_t i, size_t j, AL_OR_AU& al_or_au) const {
    int number_el = profile[i] - profile[i - 1];
    int number_zero = (int)i - 1 - number_el;
    if (number_zero < j) {
        int k = profile[i - 1] + j - number_zero;
        return al_or_au[k];
    } else {
        return zero;
    }
}

MatrixProfileFormat::T MatrixProfileFormat::operator()(size_t i, size_t j) const {
    if (i < j) {
        return get_el_in_matrix(j, i, au);
    } else if (i > j) {
        return get_el_in_matrix(i, j, al);
    } else {
        return diag[i - 1];
    }
}

MatrixProfileFormat MatrixProfileFormat::operator*(MatrixProfileFormat::T value) const {
    return MatrixProfileFormat(mul_vec(this->al, value),
                               mul_vec(this->au, value),
                               mul_vec(this->diag, value),
                               this->profile);
}

template <typename AL_OR_AU>
void MatrixProfileFormat::set_value_in_matrix(size_t i, size_t j, AL_OR_AU& al_or_au, T value) {
    int num_el = profile[i] - profile[i - 1];
    int num_zero = (int)i - 1 - num_el;
    if (num_zero < j) {
        int k = profile[i - 1] + j - num_zero;
        al_or_au[k] = value;
    } else if (value != 0.0L) {
        assert(value == 0.0L);
    }
}

void MatrixProfileFormat::set(size_t i, size_t j, MatrixProfileFormat::T value) {
    if (i == j) {
        diag[i - 1] = value;
    } else if (i > j) {
        set_value_in_matrix(i, j, al, value);
    } else {
        set_value_in_matrix(j, i, au, value);
    }
}

MatrixProfileFormat MatrixProfileFormat::toProfileFormat(Matrix matrix) {
    AL newAl;
    AU newAu;
    Diag newDiag;
    Profile newProfile(matrix.size() + 1);
    newAl.push_back(zero);
    newAu.push_back(zero);
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            newAl.push_back(matrix[i][j]);
            newAu.push_back(matrix[j][i]);
        }
    }
    for (size_t i = 0; i < matrix.size(); i++) {
        newDiag.push_back(matrix[i][i]);
    }
    for (size_t i = 1; i < newProfile.size(); i++) {
        newProfile[i] = newProfile[i - 1] + (int)i - 1;
    }
    return MatrixProfileFormat(newAl, newAu, newDiag, newProfile);
}

MatrixProfileFormat::MatrixProfileFormat(Matrix matrix)
    : MatrixProfileFormat(toProfileFormat(std::move(matrix))) {
}

Vector MatrixProfileFormat::operator*(Vector const& vector) const {
    Vector ans(vector.size());
    for (size_t i = 1; i <= dim(); i++) {
        for (size_t j = 1; j <= dim(); j++) {
            ans[i - 1] += this->operator()(i, j) * vector[j - 1];
        }
    }
    return ans;
}


std::vector<long double> MatrixProfileFormat::operator*(std::vector<long double> const& vector) const {
    std::vector<long double> ans(vector.size());
    for (size_t i = 1; i <= dim(); i++) {
        for (size_t j = 1; j <= dim(); j++) {
            ans[i - 1] += this->operator()(i, j) * vector[j - 1];
        }
    }
    return ans;
}


