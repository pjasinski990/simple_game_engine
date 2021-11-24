#include "quaternion.h"

#include "vec3.h"

namespace mrld
{
    quat::quat(float a, float b, float c, float d)
    : a{a}
    , b{b}
    , c{c}
    , d{d}
    {
        /* no-op */
    }

    quat::quat(const vec3 &u)
    {
        a = cosf(u.magnitude());
        vec3 uh = u.normalized();
        b = uh.x;
        c = uh.y;
        d = uh.z;
    }

    quat::quat(const vec3 &u, float angle)
    {
        a = cosf(angle / 2.0f);
        float temp = sinf(angle / 2.0f);
        b = temp * u.x;
        c = temp * u.y;
        d = temp * u.z;
    }

    quat &quat::operator*=(const quat &o)
    {
        quat res;
        res.a = a * o.a - b * o.b - c * o.c - d * o.d;
        res.b = a * o.b + b * o.a + c * o.d - d * o.c;
        res.c = a * o.c - b * o.d + c * o.a + d * o.b;
        res.d = a * o.d + b * o.c - c * o.b + d * o.a;
        *this = res;
        return *this;
    }

    quat operator*(quat o1, const quat &o2)
    {
        return o1 *= o2;
    }

    quat quat::conjugate() const
    {
        return quat(a, -b, -c, -d);
    }

    mat4 quat::create_rotation_matrix() const
    {
        mat4 res;
        // row0
        res.data[0 * 4 + 0] = 2.0f * (a * a + b * b) - 1.0f;
        res.data[0 * 4 + 1] = 2.0f * (b * c - a * d);
        res.data[0 * 4 + 2] = 2.0f * (b * d + a * c);

        // row1
        res.data[1 * 4 + 0] = 2.0f * (b * c + a * d);
        res.data[1 * 4 + 1] = 2.0f * (a * a + c * c) - 1.0f;
        res.data[1 * 4 + 2] = 2.0f * (c * d - a * b);

        // row2
        res.data[2 * 4 + 0] = 2.0f * (b * d - a * c);
        res.data[2 * 4 + 1] = 2.0f * (c * d + a * b);
        res.data[2 * 4 + 2] = 2.0f * (a * a + d * d) - 1.0f;

        res.data[15] = 1.0f;
        return res;
    }
}
