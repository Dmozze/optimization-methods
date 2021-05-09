
#include <vector>
#include "../second-lab/Vector.h"

class MatrixProfileFormat {

protected:
    using T = long double;
    using AL = std::vector<T>;
    using AU = AL;
    using Profile = std::vector<int>;
    using Diag = AL;

private:
    AL al{};
    AU au{};
    Profile profile{};
    Diag diag;

    T zero = 0.0L;

    template<typename AL_OR_AU>
    MatrixProfileFormat::T get_el_in_matrix(size_t i, size_t j, AL_OR_AU &al_or_au);

    template<typename Type>
    Type mul_vec(Type &vec, T value) {
        Type newVec = vec;
        for (auto &i : newVec) {
            i *= value;
        }
        return newVec;
    }

public:


    MatrixProfileFormat(AL al, AU au, Diag diag, Profile profile);

    size_t dim();

    T operator ()(size_t i, size_t j);

    MatrixProfileFormat operator + (MatrixProfileFormat &a);

    MatrixProfileFormat operator - ();

    MatrixProfileFormat operator - (MatrixProfileFormat &matrix1);

    MatrixProfileFormat operator * (T value);

    Vector operator * (Vector &vector);



};
