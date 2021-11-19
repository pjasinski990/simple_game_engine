#pragma once

#include <cmath>

namespace mrld
{
    struct vec3;
    struct quat
    {
        quat() = default;
        quat(float a, float b, float c, float d);
        explicit quat(const vec3 &u);
        quat(float angle, const vec3 &u);
        quat conjugate() const;

        quat& operator*=(const quat &o);
        friend quat operator*(quat o1, const quat &o2);

        float a, b, c, d;
    };
}
