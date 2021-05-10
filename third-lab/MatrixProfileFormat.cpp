#include "MatrixProfileFormat.h"

#include <utility>
#include <cassert>

MatrixProfileFormat::MatrixProfileFormat(AL al, AU au, Diag diag, Profile profile)
        : al(std::move(al)), au(std::move(au)), profile(std::move(profile)), diag(std::move(diag)) {
}

size_t MatrixProfileFormat::dim() {
    return profile.size() - 1;
}

template<typename AL_OR_AU>
MatrixProfileFormat::T MatrixProfileFormat::get_el_in_matrix(size_t i, size_t j, AL_OR_AU &al_or_au) {
    int number_el = profile[i] - profile[i - 1];
    int number_zero = (int) i - 1 - number_el;
    if (number_zero < j) {
        int k = profile[i - 1] + j - number_zero;
        return al_or_au[k];
    } else {
        return zero;
    }
}

MatrixProfileFormat::T MatrixProfileFormat::operator()(size_t i, size_t j) {
    if (i < j) {
        return get_el_in_matrix(j, i, au);
    } else if (i > j) {
        return get_el_in_matrix(i, j, al);
    } else {
        return diag[i - 1];
    }
}

MatrixProfileFormat MatrixProfileFormat::operator*(MatrixProfileFormat::T value) {
    return MatrixProfileFormat(mul_vec(this->al, value),
                               mul_vec(this->au, value),
                               mul_vec(this->diag, value),
                               this->profile);
}


template<typename AL_OR_AU>
void MatrixProfileFormat::set_value_in_matrix(size_t i, size_t j, AL_OR_AU &al_or_au, T value) {
    int num_el = profile[i] - profile[i - 1];
    int num_zero = (int) i - 1 - num_el;
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
        newProfile[i] = static_cast<int>(newProfile[i - 1]) + i - 1;
    }
    return MatrixProfileFormat(newAl, newAu, newDiag, newProfile);
}

MatrixProfileFormat::MatrixProfileFormat(Matrix matrix) : MatrixProfileFormat(toProfileFormat(std::move(matrix))) {
}
