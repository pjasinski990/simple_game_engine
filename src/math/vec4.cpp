#include <tuple>
#include <cmath>

#include "math_util.h"
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

    vec4& vec4::operator+=(float f)
    {
        *this += vec4(f, f, f, f);
        return *this;
    }
    vec4& vec4::operator-=(float f)
    {
        *this -= vec4(f, f, f, f);
        return *this;
    }
    vec4& vec4::operator*=(float f)
    {
        *this *= vec4(f, f, f, f);
        return *this;
    }
    vec4& vec4::operator/=(float f)
    {
        *this /= vec4(f, f, f, f);
        return *this;
    }

    vec4 operator+(vec4 o, float f)
    {
        return vec4(o) += f;
    }
    vec4 operator-(vec4 o, float f)
    {
        return vec4(o) -= f;
    }
    vec4 operator*(vec4 o, float f)
    {
        return vec4(o) *= f;
    }
    vec4 operator/(vec4 o, float f)
    {
        return vec4(o) /= f;
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
        bool rx = (o1.x - o2.x) <= (fabs(o1.x) < fabs(o2.x) ? fabs(o1.x) : fabs(o2.x) * math_constants::epsilon);
        if (!rx) { return false; }
        bool ry = (o1.y - o2.y) <= (fabs(o1.y) < fabs(o2.y) ? fabs(o1.y) : fabs(o2.y) * math_constants::epsilon);
        if (!ry) { return false; }
        bool rz = (o1.z - o2.z) <= (fabs(o1.z) < fabs(o2.z) ? fabs(o1.z) : fabs(o2.z) * math_constants::epsilon);
        if (!rz) { return false; }
        return (o1.w - o2.w) <= (fabs(o1.w) < fabs(o2.w) ? fabs(o1.w) : fabs(o2.w) * math_constants::epsilon);
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
        return sqrtf(x*x + y*y + z*z + w*w);
    }
    vec4 vec4::normalized() const
    {
        return *this / magnitude();
    }
};
