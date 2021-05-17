#include "math/matrix_factory.h"

namespace mrld
{
    mat4 MatrixFactory::zero()
    {
        mat4 temp;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                temp[i][j] = 0.0f;
            }
        }
        return temp;
    }
    mat4 MatrixFactory::identity()
    {
        mat4 temp = MatrixFactory::zero();
        for (int i = 0; i < 4; ++i) {
            temp[i][i] = 1.0f;
        }
        return temp;
    }

}
