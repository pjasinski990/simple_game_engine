#ifndef MRLD_ENGINE_VEC4_H
#define MRLD_ENGINE_VEC4_H

#include <iostream>

#include <math/constants.h>

namespace mrld 
{
    struct vec4 
    {
        vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f); 

        vec4& operator+=(const vec4& o);
        vec4& operator-=(const vec4& o);
        vec4& operator*=(const vec4& o);
        vec4& operator/=(const vec4& o);

        friend vec4 operator+(vec4 o1, const vec4& o2);
        friend vec4 operator-(vec4 o1, const vec4& o2);
        friend vec4 operator*(vec4 o1, const vec4& o2);
        friend vec4 operator/(vec4 o1, const vec4& o2);

        vec4& operator+=(float f);
        vec4& operator-=(float f);
        vec4& operator*=(float f);
        vec4& operator/=(float f);

        friend vec4 operator+(vec4 o1, float f);
        friend vec4 operator-(vec4 o1, float f);
        friend vec4 operator*(vec4 o1, float f);
        friend vec4 operator/(vec4 o1, float f);

        friend bool operator<(const vec4& o1, const vec4& o2);
        friend bool operator>(const vec4& o1, const vec4& o2);
        friend bool operator<=(const vec4& o1, const vec4& o2);
        friend bool operator>=(const vec4& o1, const vec4& o2);
        friend bool operator==(const vec4& o1, const vec4& o2);
        friend bool operator!=(const vec4& o1, const vec4& o2); 

        friend std::ostream& operator<<(std::ostream& out, const vec4& o);

        float dot(const vec4 &o) const;

        float magnitude() const;
        vec4 normalized() const;

        float x;
        float y;
        float z;
        float w;
    };
}

#endif //MRLD_ENGINE_VEC4_H
