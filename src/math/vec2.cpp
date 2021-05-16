#include <tuple>
#include <cmath>

#include <math/vec2.h>

namespace mrld 
{
    vec2::vec2(float x, float y): x{x}, y{y} {}

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
        return std::tie(o1.x, o1.y) < std::tie(o2.x, o2.y);
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
        bool rx = (o1.x - o2.x) <= (fabs(o1.x) < fabs(o2.x) ? fabs(o1.x) : fabs(o2.x) * EPSILON);
        if (!rx) { return false; }
        return (o1.y - o2.y) <= (fabs(o1.y) < fabs(o2.y) ? fabs(o1.y) : fabs(o2.y) * EPSILON);
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
        return sqrt(x*x + y*y);
    }
    vec2 vec2::normalized() const 
    {
        return *this / magnitude();
    }
}
