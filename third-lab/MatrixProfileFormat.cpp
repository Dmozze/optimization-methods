#include "MatrixProfileFormat.h"

#include <utility>
#include <cassert>

MatrixProfileFormat::MatrixProfileFormat(AL al, AU au, Profile profile, Diag diag) :
                                         al(std::move(al)),
                                         au(std::move(au)),
                                         profile(std::move(profile)),
                                         diag(std::move(diag)){}

size_t MatrixProfileFormat::dim() {
    return profile.size();
}

MatrixProfileFormat::T get_el_in_matrix() {

}

MatrixProfileFormat::T MatrixProfileFormat::get_el_in_matrix(size_t i, size_t j, AL &al_or_au) {
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




