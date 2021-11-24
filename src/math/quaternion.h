#pragma once

#include <cmath>

#include "mat4.h"

namespace mrld
{
    struct vec3;
    struct quat
    {
        quat() = default;
        quat(float a, float b, float c, float d);
        explicit quat(const vec3 &u);
        quat(const vec3 &axis, float angle_rads);
        quat conjugate() const;
        mat4 create_rotation_matrix() const;

        quat& operator*=(const quat &o);
        friend quat operator*(quat o1, const quat &o2);

        float a, b, c, d;
    };
}
