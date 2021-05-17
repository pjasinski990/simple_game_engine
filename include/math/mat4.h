#ifndef MRLD_ENGINE_MAT4_H
#define MRLD_ENGINE_MAT4_H

#include <iostream>

namespace mrld
{
    struct mat4
    {
        float* operator[] (int i);
        const float* operator[] (int i) const;

        mat4& operator+=(const mat4& o);
        mat4& operator-=(const mat4& o);
        mat4& operator*=(const mat4& o);
        mat4& operator*=(float f);

        friend mat4 operator+(mat4 o1, const mat4 &o2);
        friend mat4 operator-(mat4 o1, const mat4 &o2);
        friend mat4 operator*(mat4 o1, const mat4 &o2);
        friend mat4 operator*(mat4 o1, float f);

        friend std::ostream& operator<<(std::ostream& out, const mat4 &o);

        float data[4][4];
    };
}

#endif //MRLD_ENGINE_MAT4_H
