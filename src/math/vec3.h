#pragma once

#include <iostream>

namespace mrld
{
    struct vec3
    {
        explicit vec3(float x, float y, float z);
        explicit vec3(float f = 0.0f);

        float& operator[](int i);
        float operator[](int i) const;

        vec3& operator+=(const vec3& o);
        vec3& operator-=(const vec3& o);
        vec3& operator*=(float f);
        vec3& operator/=(float f);

        friend vec3 operator+(vec3 o, const vec3& o2);
        friend vec3 operator-(vec3 o, const vec3& o2);
        friend vec3 operator*(vec3 o, float f);
        friend vec3 operator/(vec3 o, float f);
        friend vec3 operator*(float f, vec3 o);
        friend vec3 operator/(float f, vec3 o);

        friend bool operator<(const vec3& o1, const vec3& o2);
        friend bool operator>(const vec3& o1, const vec3& o2);
        friend bool operator<=(const vec3& o1, const vec3& o2);
        friend bool operator>=(const vec3& o1, const vec3& o2);
        friend bool operator==(const vec3& o1, const vec3& o2);
        friend bool operator!=(const vec3& o1, const vec3& o2);

        friend std::ostream& operator<<(std::ostream& out, const vec3& o);

        float dot(const vec3 &o) const;
        vec3 cross(const vec3 &o) const;

        float magnitude() const;
        float magnitude_squared() const;
        vec3 normalized() const;

        float x;
        float y;
        float z;
    };

    namespace unit_vec
    {
        const vec3 x = vec3(1.0f, 0.0f, 0.0f);
        const vec3 y = vec3(0.0f, 1.0f, 0.0f);
        const vec3 z = vec3(0.0f, 0.0f, 1.0f);
    }
};
