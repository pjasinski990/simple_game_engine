#include <cmath>

#include "vec4.h"

namespace mrld
{
    vec4::vec4(float x, float y, float z, float w): x{x}, y{y}, z{z}, w{w} {}

    float& vec4::operator[](int i)
    {
        if (i == 0) {return x;}
        if (i == 1) {return y;}
        if (i == 2) {return z;}
        if (i == 3) {return w;}
        throw std::out_of_range("Indexing error in vec4: out of range");
    }
    float vec4::operator[](int i) const
    {
        if (i == 0) {return x;}
        if (i == 1) {return y;}
        if (i == 2) {return z;}
        if (i == 3) {return w;}
        throw std::out_of_range("Indexing error in vec4: out of range");
    }

    vec4& vec4::operator+=(const vec4& o)
    {
        this->x += o.x;
        this->y += o.y;
        this->z += o.z;
        this->w += o.w;
        return *this;
    }
    vec4& vec4::operator-=(const vec4& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        this->z -= o.z;
        this->w -= o.w;
        return *this;
    }
    vec4& vec4::operator*=(float f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        this->w *= f;
        return *this;
    }
    vec4& vec4::operator/=(float f)
    {
        this->x /= f;
        this->y /= f;
        this->z /= f;
        this->w /= f;
        return *this;
    }

    vec4 operator+(vec4 o1, const vec4& o2)
    {
        return o1 += o2;
    }
    vec4 operator-(vec4 o1, const vec4& o2)
    {
        return o1 -= o2;
    }
    vec4 operator*(vec4 o, float f)
    {
        return o *= f;
    }
    vec4 operator/(vec4 o, float f)
    {
        return o /= f;
    }
    vec4 operator*(float f, vec4 o)
    {
        return o *= f;
    }
    vec4 operator/(float f, vec4 o)
    {
        return o /= f;
    }

    bool operator<(const vec4& o1, const vec4& o2)
    {
        return o1.magnitude_squared() < o2.magnitude_squared();
    }
    bool operator>(const vec4& o1, const vec4& o2)
    {
        return o2 < o1;
    }
    bool operator<=(const vec4& o1, const vec4& o2)
    {
        return !(o2 < o1);
    }
    bool operator>=(const vec4& o1, const vec4& o2)
    {
        return !(o1 < o2);
    }
    bool operator==(const vec4& o1, const vec4& o2)
    {
        return o1.magnitude_squared() == o2.magnitude_squared();
    }
    bool operator!=(const vec4& o1, const vec4& o2)
    {
        return !(o1 == o2);
    }

    std::ostream& operator<<(std::ostream& out, const vec4& o)
    {
        out << "[" << o.x << ", " << o.y << ", " << o.z << ", " << o.w <<  "]";
        return out;
    }

    float vec4::dot(const vec4 &o) const
    {
        return this->x * o.x + this->y + o.y + this->z * o.z + this->w * o.w;
    }

    float vec4::magnitude() const
    {
        return sqrtf(magnitude_squared());
    }
    float vec4::magnitude_squared() const
    {
        return x*x + y*y + z*z + w*w;
    }
    vec4 vec4::normalized() const
    {
        return *this / magnitude();
    }
};
