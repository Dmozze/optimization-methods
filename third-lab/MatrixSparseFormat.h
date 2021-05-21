#pragma once


#include <vector>
#include <algebra/Vector.h>

class MatrixSparseFormat {
    using T = long double;
    using ALU = std::vector<T>;
    using Diag = ALU;
    using Profile = std::vector<int>;
    using Indexes = std::vector<size_t>;

    ALU alu;
    Diag diag;
    Profile profile;
    Indexes indexes;

    size_t search_index(size_t i, size_t j) const;

    MatrixSparseFormat::T zero = 0.0L;

    MatrixSparseFormat::T get_element(size_t i, size_t j, const ALU &alu) const;


public:

    MatrixSparseFormat(ALU alu, Diag diag, Profile profile, Indexes indexes);

    size_t dim() const;

    T operator()(size_t i, size_t j) const;

    Vector operator*(Vector const& vector) const;

};
