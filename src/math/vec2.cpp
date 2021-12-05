#include <tuple>
#include <cmath>
#include <stdexcept>

#include "math_util.h"
#include "vec2.h"

namespace mrld 
{
    vec2::vec2(float x, float y): x{x}, y{y} {}

    float& vec2::operator[](int i)
    {
        if (i == 0) {return x;}
        if (i == 1) {return y;}
        throw std::out_of_range("Indexing error in vec2: out of range");
    }
    float vec2::operator[](int i) const
    {
        if (i == 0) {return x;}
        if (i == 1) {return y;}
        throw std::out_of_range("Indexing error in vec2: out of range");
    }

    vec2& vec2::operator+=(const vec2& o)
    {
        this->x += o.x;
        this->y += o.y;
        return *this;
    }
    vec2& vec2::operator-=(const vec2& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        return *this;
    }
    vec2& vec2::operator*=(const vec2& o)
    {
        this->x *= o.x;
        this->y *= o.y;
        return *this;
    }
    vec2& vec2::operator/=(const vec2& o)
    {
        this->x /= o.x;
        this->y /= o.y;
        return *this;
    }


    vec2 operator+(vec2 o1, const vec2& o2)
    {
        return o1 += o2;
    }
    vec2 operator-(vec2 o1, const vec2& o2)
    {
        return o1 -= o2;
    }
    vec2 operator*(vec2 o1, const vec2& o2)
    {
        return o1 *= o2;
    }
    vec2 operator/(vec2 o1, const vec2& o2)
    {
        return o1 /= o2;
    }

    vec2& vec2::operator+=(float f)
    {
        *this += vec2(f, f);
        return *this;
    }
    vec2& vec2::operator-=(float f)
    {
        *this -= vec2(f, f);
        return *this;
    }
    vec2& vec2::operator*=(float f)
    {
        *this *= vec2(f, f);
        return *this;
    }
    vec2& vec2::operator/=(float f)
    {
        *this /= vec2(f, f);
        return *this;
    }

    vec2 operator+(vec2 o, float f)
    {
        return vec2(o) += f;
    }
    vec2 operator-(vec2 o, float f)
    {
        return vec2(o) -= f;
    }
    vec2 operator*(vec2 o, float f)
    {
        return vec2(o) *= f;
    }
    vec2 operator/(vec2 o, float f)
    {
        return vec2(o) /= f;
    }

    bool operator<(const vec2& o1, const vec2& o2)
    {
        return o1.magnitude_squared() < o2.magnitude_squared();
    }
    bool operator>(const vec2& o1, const vec2& o2)
    {
        return o2 < o1;
    }
    bool operator<=(const vec2& o1, const vec2& o2)
    {
        return !(o2 < o1);
    }
    bool operator>=(const vec2& o1, const vec2& o2)
    {
        return !(o1 < o2);
    }
    bool operator==(const vec2& o1, const vec2& o2)
    {
        bool rx = (o1.x - o2.x) <= (fabs(o1.x) < fabs(o2.x) ? fabs(o1.x) : fabs(o2.x) * math_constants::epsilon);
        if (!rx) { return false; }
        return (o1.y - o2.y) <= (fabs(o1.y) < fabs(o2.y) ? fabs(o1.y) : fabs(o2.y) * math_constants::epsilon);
    }
    bool operator!=(const vec2& o1, const vec2& o2)
    {
        return !(o1 == o2);
    }

    std::ostream& operator<<(std::ostream& out, const vec2& o)
    {
        out << "[" << o.x << ", " << o.y << "]";
        return out;
    }

    float vec2::dot(const vec2 &o) const
    {
        return this->x * o.x + this->y + o.y;
    }

    float vec2::magnitude() const 
    {
        return sqrtf(magnitude_squared());
    }
    float vec2::magnitude_squared() const
    {
        return x*x + y*y;
    }
    vec2 vec2::normalized() const
    {
        return *this / magnitude();
    }
}
