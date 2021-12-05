#pragma once

#include "../../math/vec3.h"
#include "../body.h"

namespace mrld
{
    struct collision_point
    {
        vec3 a;                 // deepest point of body A in body B
        vec3 b;                 // deepest point of body B in body A
        vec3 normal;            // b - a normalized (points towards body A)
        float collision_depth;  // distance between a and b
        bool has_collision;
    };
}
