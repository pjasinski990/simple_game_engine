#ifndef MRLD_ENGINE_VEC3_H
#define MRLD_ENGINE_VEC3_H

#include <iostream>

#include <math/constants.h>

namespace mrld 
{
    struct vec3 
    {
        vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f); 

        vec3& operator+=(const vec3& o);
        vec3& operator-=(const vec3& o);
        vec3& operator*=(const vec3& o);
        vec3& operator/=(const vec3& o);

        friend vec3 operator+(vec3 o1, const vec3& o2);
        friend vec3 operator-(vec3 o1, const vec3& o2);
        friend vec3 operator*(vec3 o1, const vec3& o2);
        friend vec3 operator/(vec3 o1, const vec3& o2);

        friend bool operator<(const vec3& o1, const vec3& o2);
        friend bool operator>(const vec3& o1, const vec3& o2);
        friend bool operator<=(const vec3& o1, const vec3& o2);
        friend bool operator>=(const vec3& o1, const vec3& o2);
        friend bool operator==(const vec3& o1, const vec3& o2);
        friend bool operator!=(const vec3& o1, const vec3& o2); 

        friend std::ostream& operator<<(std::ostream& out, const vec3& o);

        float dot(const vec3 &o) const;
        vec3 cross(const vec3 &o) const;

        float x;
        float y;
        float z;
    };
};

#endif //MRLD_ENGINE_VEC3_H
