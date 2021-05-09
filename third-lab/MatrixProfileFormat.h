
#include <vector>
#include "../second-lab/Vector.h"

class MatrixProfileFormat {

    using T = long double;
    using AL = std::vector<T>;
    using AU = AL;
    using Profile = std::vector<int>;

    AL al{};
    AU au{};
    Profile profile{};

public:


    MatrixProfileFormat(AL al, AU au, Profile profile);

    size_t dim();

    T& operator ()(size_t i, size_t j);

    MatrixProfileFormat operator + (MatrixProfileFormat &a);

    MatrixProfileFormat operator - ();

    MatrixProfileFormat operator - (MatrixProfileFormat &matrix1);

    MatrixProfileFormat operator * (T value);

    Vector operator * (Vector &vector);


};
