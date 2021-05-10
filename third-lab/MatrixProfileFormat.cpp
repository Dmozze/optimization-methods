#include "MatrixProfileFormat.h"

#include <utility>
#include <cassert>

MatrixProfileFormat::MatrixProfileFormat(AL al, AU au, Diag diag, Profile profile)
    : al(std::move(al))
    , au(std::move(au))
    , profile(std::move(profile))
    , diag(std::move(diag)) {
}

size_t MatrixProfileFormat::dim() {
    return diag.size();
}

template <typename AL_OR_AU>
MatrixProfileFormat::T MatrixProfileFormat::get_el_in_matrix(size_t i, size_t j, AL_OR_AU& al_or_au) {
    // i > j
    int number_el = profile[j] - profile[j - 1];
    if (i - j <= number_el) {
        int k = profile[j - 1] + i - j;
        return al_or_au[k];
    } else {
        return zero;
    }
}

MatrixProfileFormat::T MatrixProfileFormat::operator()(size_t i, size_t j) {
    if (i > j) {
        return get_el_in_matrix(i, j, al);
    } else if (i < j) {
        return get_el_in_matrix(j, i, au);
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
    // i > j
    int num_el = profile[j] - profile[j - 1];
    if (i - j <= num_el) {
        int k = profile[j - 1] + i - j;
        al_or_au[k] = value;
    } else {
        assert(value == 0.0L);
    }
}


void MatrixProfileFormat::set(size_t i, size_t j, MatrixProfileFormat::T value) {
    if (i == j) {
        diag[i - 1] = value;
    } else if (i < j) {
        set_value_in_matrix(j, i, au, value);
    } else {
        set_value_in_matrix(i, j, al, value);
    }
}

int MatrixProfileFormat::number_of_elements(size_t i) {
    return profile[i] - profile[i - 1];
}

