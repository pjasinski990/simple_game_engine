#ifndef MRLD_ENGINE_MATRIX_FACTORY_H
#define MRLD_ENGINE_MATRIX_FACTORY_H

#include <math/mat4.h>

namespace mrld
{
    class MatrixFactory
    {
    public:
        static mat4 zero();
        static mat4 identity();
    };
}

#endif //MRLD_ENGINE_MATRIX_FACTORY_H
