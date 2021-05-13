//
// Created by andrey on 13.05.2021.
//

#include "MatrixSparseFormat.h"

#include <utility>

MatrixSparseFormat::MatrixSparseFormat(MatrixSparseFormat::AL al, MatrixSparseFormat::AU au,
                                       MatrixSparseFormat::Diag diag, MatrixSparseFormat::Profile profile,
                                       MatrixSparseFormat::Indexes indexes) : al(std::move(al)), au(std::move(au)),
                                                                              diag(std::move(diag)),
                                                                              profile(std::move(profile)),
                                                                              indexes(std::move(indexes)) {}

size_t MatrixSparseFormat::dim() {
    return diag.size();
}

// i > j
size_t MatrixSparseFormat::search_index(size_t i, size_t j) {
    int number_of_elements = profile[i] - profile[i - 1];
    size_t answer = profile[i - 1] + 1;
    for (int J = (number_of_elements + 1) / 2; J > 0; J /= 2) {
        while (answer + J <= profile[i] && indexes[answer + J] <= j) {
            answer += J;
        }
    }
    return answer;
}


MatrixSparseFormat::T MatrixSparseFormat::operator()(size_t i, size_t j) {
    if (i == j) {
        return diag[i - 1];
    } else if (i < j) {
        return get_element(j, i, au);
    } else {
        return get_element(i, j, al);
    }
}

//i < j
template<typename AL_OR_AU>
MatrixSparseFormat::T MatrixSparseFormat::get_element(size_t i, size_t j, AL_OR_AU &al_or_au) {
    size_t index = search_index(i, j);
    if (indexes[index] == j) {
        return al_or_au[indexes[index]];
    } else {
        return zero;
    }
}









