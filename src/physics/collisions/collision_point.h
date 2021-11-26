#pragma once

#include "../../math/vec3.h"

namespace mrld
{
    struct collision_point
    {
        vec3 a;         // deepest point of obj A in obj B
        vec3 b;         // deepest point of obj B in obj A
        vec3 normal;    // b - a normalized
        bool has_collision;
    };
}
