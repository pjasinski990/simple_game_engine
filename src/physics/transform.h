#pragma once

#include "../math/vec3.h"
#include "../math/quaternion.h"

namespace mrld
{
    struct transform
    {
        vec3 position;
        vec3 scale;
        quat rotation;
    };
}
