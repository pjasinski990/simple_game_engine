#pragma once
#include "../math/vec3.h"

namespace mrld
{


    struct physics_properties {
        vec3 position;
        vec3 velocity;
        vec3 acceleration;
        float bounciness;
        float mass;
    };
}
