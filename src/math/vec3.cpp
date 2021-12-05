#include <cmath>

#include "vec3.h"

namespace mrld
{
    vec3::vec3(float x, float y, float z): x{x}, y{y}, z{z} {}

    float& vec3::operator[](int i)
    {
        if (i == 0) {return x;}
        if (i == 1) {return y;}
        if (i == 2) {return z;}
        throw std::out_of_range("Indexing error in vec3: out of range");
    }
    float vec3::operator[](int i) const
    {
        if (i == 0) {return x;}
        if (i == 1) {return y;}
        if (i == 2) {return z;}
        throw std::out_of_range("Indexing error in vec3: out of range");
    }

    vec3& vec3::operator+=(const vec3& o)
    {
        this->x += o.x;
        this->y += o.y;
        this->z += o.z;
        return *this;
    }
    vec3& vec3::operator-=(const vec3& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        this->z -= o.z;
        return *this;
    }
    vec3& vec3::operator*=(float f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
    }
    vec3& vec3::operator/=(float f)
    {
        this->x /= f;
        this->y /= f;
        this->z /= f;
        return *this;
    }

    vec3 operator+(vec3 o1, const vec3& o2)
    {
        return o1 += o2;
    }
    vec3 operator-(vec3 o1, const vec3& o2)
    {
        return o1 -= o2;
    }
    vec3 operator*(vec3 o, float f)
    {
        return o *= f;
    }
    vec3 operator/(vec3 o, float f)
    {
        return o /= f;
    }
    vec3 operator*(float f, vec3 o)
    {
        return o *= f;
    }
    vec3 operator/(float f, vec3 o)
    {
        return o /= f;
    }

    bool operator<(const vec3& o1, const vec3& o2)
    {
        return o1.magnitude_squared() < o2.magnitude_squared();
    }
    bool operator>(const vec3& o1, const vec3& o2)
    {
        return o2 < o1;
    }
    bool operator<=(const vec3& o1, const vec3& o2)
    {
        return !(o2 < o1);
    }
    bool operator>=(const vec3& o1, const vec3& o2)
    {
        return !(o1 < o2);
    }
    bool operator==(const vec3& o1, const vec3& o2)
    {
        return o1.magnitude_squared() == o2.magnitude_squared();
    }
    bool operator!=(const vec3& o1, const vec3& o2)
    {
        return !(o1 == o2);
    }

    std::ostream& operator<<(std::ostream& out, const vec3& o)
    {
        out << "[" << o.x << ", " << o.y << ", " << o.z << "]";
        return out;
    }

    float vec3::dot(const vec3 &o) const
    {
        return this->x*o.x + this->y*o.y + this->z*o.z;
    }
    vec3 vec3::cross(const vec3& o) const
    {
        return vec3(
            this->y * o.z - this->z * o.y,
            this->z * o.x - this->x * o.z,
            this->x * o.y - this->y * o.x
            );
    }

    float vec3::magnitude() const
    {
        return sqrtf(magnitude_squared());
    }
    float vec3::magnitude_squared() const {
        return x*x + y*y + z*z;
    }
    vec3 vec3::normalized() const
    {
        return *this / magnitude();
    }
}
