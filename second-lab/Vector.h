#pragma once
#include <vector>


class Vector {
    using T = long double;
    using Vector_type = std::vector<T>;

    Vector_type v;

public:

    Vector(size_t n);

    Vector(Vector_type &vec);

    size_t size();

    T& operator[] (size_t &index);

    Vector operator + (Vector &vector);

    Vector operator - ();

    Vector operator - (Vector &vector);

    T operator * (Vector &vector);

    Vector operator * (T value);
};

