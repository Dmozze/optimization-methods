#include "MatrixProfileFormat.h"


MatrixProfileFormat::MatrixProfileFormat(MatrixProfileFormat::AL al, MatrixProfileFormat::AU au,
                                         MatrixProfileFormat::Profile profile) :
                                         al(al),
                                         au(au),
                                         profile(profile) {}

size_t MatrixProfileFormat::dim() {
    return profile.size();
}


