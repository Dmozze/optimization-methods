//
// Created by andrey on 13.05.2021.
//

#include "MatrixSparseFormat.h"

#include <utility>

MatrixSparseFormat::MatrixSparseFormat(ALU alu, Diag diag, Profile profile, Indexes indexes)
        : alu(std::move(alu)),
          diag(std::move(diag)),
          profile(std::move(profile)),
          indexes(std::move(indexes)) {}

size_t MatrixSparseFormat::dim() const {
    return diag.size();
}

// i > j
size_t MatrixSparseFormat::search_index(size_t i, size_t j) const {
    int number_of_elements = profile[i] - profile[i - 1];
    size_t answer = profile[i - 1] + 1;
    for (int J = (number_of_elements + 1) / 2; J > 0; J /= 2) {
        while (answer + J <= profile[i] && indexes[answer + J] <= j) {
            answer += J;
        }
    }
    return answer;
}


MatrixSparseFormat::T MatrixSparseFormat::operator()(size_t i, size_t j) const {
    if (i == j) {
        return diag[i - 1];
    } else if (i < j) {
        std::swap(i, j);
    }
    return get_element(i, j, alu);
}

// i > j
MatrixSparseFormat::T MatrixSparseFormat::get_element(size_t i, size_t j, const ALU &alu1) const {
    size_t index = search_index(i, j);
    if (index < indexes.size() && indexes[index] == j) {
        return alu1[index];
    } else {
        return zero;
    }
}

Vector MatrixSparseFormat::operator*(const Vector &vector) const {
    Vector ans(vector.size());
    for (size_t i = 1; i <= dim(); i++) {
        for (size_t j = 1; j <= dim(); j++) {
            ans[i - 1] += this->operator()(i, j) * vector[j - 1];
        }
    }
    return ans;
}

void MatrixSparseFormat::set_diag_element(const size_t index_diag_element, MatrixSparseFormat::T set_element) {
    diag[index_diag_element] = set_element;
}

void MatrixSparseFormat::print(std::ostream &out) const {
    for (size_t i = 1; i <= dim(); i++) {
        for (size_t j = 1; j <= dim(); j++) {
            out << this->operator()(i, j) << ' ';
        }
        out << std::endl;
    }
}









