#pragma once


#include <vector>

class MatrixSparseFormat {
    using T = long double;
    using AL = std::vector<T>;
    using AU = AL;
    using Diag = AL;
    using Profile = std::vector<int>;
    using Indexes = std::vector<size_t>;

    AL al;
    AU au;
    Diag diag;
    Profile profile;
    Indexes indexes;

    // i < j
    size_t search_index(size_t i, size_t j);

    MatrixSparseFormat::T zero = 0.0L;

    template<typename AL_OR_AU>
    MatrixSparseFormat::T get_element(size_t i, size_t j, AL_OR_AU &al_or_au);


public:

    MatrixSparseFormat(AL al, AU au, Diag diag, Profile profile, Indexes indexes);

    size_t dim();

    T operator()(size_t i, size_t j);
};
