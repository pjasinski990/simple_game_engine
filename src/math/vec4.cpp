#include <tuple>
#include <cmath>

#include <math/vec4.h>

namespace mrld 
{
    vec4::vec4(float x, float y, float z, float w): x{x}, y{y}, z{z}, w{w} {}

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
    vec4& vec4::operator*=(const vec4& o)
    {
        this->x *= o.x;
        this->y *= o.y;
        this->z *= o.z;
        this->w *= o.w;
        return *this;
    }
    vec4& vec4::operator/=(const vec4& o)
    {
        this->x /= o.x;
        this->y /= o.y;
        this->z /= o.z;
        this->w /= o.w;
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
    vec4 operator*(vec4 o1, const vec4& o2)
    {
        return o1 *= o2;
    }
    vec4 operator/(vec4 o1, const vec4& o2)
    {
        return o1 /= o2;
    }

    bool operator<(const vec4& o1, const vec4& o2)
    {
        return std::tie(o1.x, o1.y, o1.z, o1.w) < std::tie(o2.x, o2.y, o2.z, o2.w);
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
        bool rx = (o1.x - o2.x) <= (fabs(o1.x) < fabs(o2.x) ? fabs(o1.x) : fabs(o2.x) * EPSILON);
        if (!rx) { return false; }
        bool ry = (o1.y - o2.y) <= (fabs(o1.y) < fabs(o2.y) ? fabs(o1.y) : fabs(o2.y) * EPSILON);
        if (!ry) { return false; }
        bool rz = (o1.z - o2.z) <= (fabs(o1.z) < fabs(o2.z) ? fabs(o1.z) : fabs(o2.z) * EPSILON);
        if (!rz) { return false; }
        return (o1.w - o2.w) <= (fabs(o1.w) < fabs(o2.w) ? fabs(o1.w) : fabs(o2.w) * EPSILON);
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
};

