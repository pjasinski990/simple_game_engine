#pragma once

#include <iostream>

namespace mrld
{
    struct vec2 
    {
        explicit vec2(float x, float y);
        explicit vec2(float f = 0.0f);

        float& operator[](int i);
        float operator[](int i) const;

        vec2& operator+=(const vec2& o);
        vec2& operator-=(const vec2& o);

        vec2& operator*=(float f);
        vec2& operator/=(float f);

        friend vec2 operator*(vec2 o, float f);
        friend vec2 operator/(vec2 o, float f);
        friend vec2 operator*(float f, vec2 o);
        friend vec2 operator/(float f, vec2 o);

        friend vec2 operator+(vec2 o1, const vec2& o2);
        friend vec2 operator-(vec2 o1, const vec2& o2);

        friend bool operator<(const vec2& o1, const vec2& o2);
        friend bool operator>(const vec2& o1, const vec2& o2);
        friend bool operator<=(const vec2& o1, const vec2& o2);
        friend bool operator>=(const vec2& o1, const vec2& o2);
        friend bool operator==(const vec2& o1, const vec2& o2);
        friend bool operator!=(const vec2& o1, const vec2& o2); 

        friend std::ostream& operator<<(std::ostream& out, const vec2& o);

        float dot(const vec2 &o) const;
        
        float magnitude() const;
        float magnitude_squared() const;
        vec2 normalized() const;

        float x;
        float y;
    };
};
