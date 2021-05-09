#include "MatrixProfileFormat.h"

#include <utility>
#include <cassert>

MatrixProfileFormat::MatrixProfileFormat(AL al, AU au, Diag diag, Profile profile) :
                                         al(std::move(al)),
                                         au(std::move(au)),
                                         profile(std::move(profile)),
                                         diag(std::move(diag)){}

size_t MatrixProfileFormat::dim() {
    return profile.size();
}

template<typename AL_OR_AU>
MatrixProfileFormat::T MatrixProfileFormat::get_el_in_matrix(size_t i, size_t j, AL_OR_AU &al_or_au) {
    int number_el = profile[i] - profile[i - 1];
    int number_zero = (int)i - 1 - number_el;
    if (number_zero < j ) {
        return al_or_au[profile[i - 1] + j - number_zero];
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
        return diag[i];
    }
}



MatrixProfileFormat MatrixProfileFormat::operator*(MatrixProfileFormat::T value) {
    return MatrixProfileFormat(mul_vec(this->al, value),
                               mul_vec(this->au, value),
                               mul_vec(this->diag, value),
                               this->profile);
}






