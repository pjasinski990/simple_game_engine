#include <math/mat4.h>

namespace mrld
{
    float* mat4::operator[] (int i)
    {
        return data[i];
    }
    const float* mat4::operator[] (int i) const
    {
        return data[i];
    }

    mat4& mat4::operator+=(const mat4 &o)
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)[i][j] += o[i][j];
            }
        }
        return *this;
    }
    mat4& mat4::operator-=(const mat4 &o)
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)[i][j] -= o[i][j];
            }
        }
        return *this;
    }
    mat4& mat4::operator*=(const mat4 &o)
    {
        mat4 temp;
        for (int i = 0; i < 4; ++i) {
            for (int k = 0; k < 4; ++k) {
                for (int j = 0; j < 4; ++j) {
                    temp[i][j] += (*this)[i][k] * o[k][j];
                }
            }
        }
        *this = std::move(temp);
        return *this;
    }
    mat4& mat4::operator*=(float f)
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)[i][j] *= f;
            }
        }
        return *this;
    }

    mat4 operator+(mat4 o1, const mat4 &o2)
    {
        return o1 += o2;
    }
    mat4 operator-(mat4 o1, const mat4& o2)
    {
        return o1 -= o2;
    }
    mat4 operator*(mat4 o1, const mat4& o2)
    {
        return o1 *= o2;
    }
    mat4 operator*(mat4 o1, float f)
    {
        return o1 *= f;
    }

    std::ostream &operator<<(std::ostream &out, const mat4 &o)
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                out << o[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }
}
