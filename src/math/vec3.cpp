#include <tuple>
#include <cmath>

#include <math/vec3.h>

namespace mrld 
{
    vec3::vec3(float x, float y, float z): x{x}, y{y}, z{z} {}

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
    vec3& vec3::operator*=(const vec3& o)
    {
        this->x *= o.x;
        this->y *= o.y;
        this->z *= o.z;
        return *this;
    }
    vec3& vec3::operator/=(const vec3& o)
    {
        this->x /= o.x;
        this->y /= o.y;
        this->z /= o.z;
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
    vec3 operator*(vec3 o1, const vec3& o2)
    {
        return o1 *= o2;
    }
    vec3 operator/(vec3 o1, const vec3& o2)
    {
        return o1 /= o2;
    }

    bool operator<(const vec3& o1, const vec3& o2)
    {
        return std::tie(o1.x, o1.y, o1.z) < std::tie(o2.x, o2.y, o2.z);
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
        bool rx = (o1.x - o2.x) <= (fabs(o1.x) < fabs(o2.x) ? fabs(o1.x) : fabs(o2.x) * EPSILON);
        if (!rx) { return false; }
        bool ry = (o1.y - o2.y) <= (fabs(o1.y) < fabs(o2.y) ? fabs(o1.y) : fabs(o2.y) * EPSILON);
        if (!ry) { return false; }
        return (o1.z - o2.z) <= (fabs(o1.z) < fabs(o2.z) ? fabs(o1.z) : fabs(o2.z) * EPSILON);
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
        return this->x * o.x + this->y + o.y + this->z * o.z;
    }
    vec3 vec3::cross(const vec3& o) const
    {
        float rx = this->y * o.z - this->z * o.y;
        float ry = -1.0f * (this->x * o.z - this->z * o.x);
        float rz = this->x * o.y - this->y * o.x;
        return vec3(rx, ry, rz);
    }
};

