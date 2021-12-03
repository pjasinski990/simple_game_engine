#pragma once
#include "../math/vec3.h"

namespace mrld
{
    struct physics_properties {
        physics_properties()
        : velocity{vec3()}
        , acceleration{vec3()}
        , bounciness{1.0f}
        , friction_s{0.5f}
        , friction_d{0.5f}
        , mass{1.0f}
        , mass_inv{1.0f}
        {
            /* no-op */
        }

        vec3 velocity;
        vec3 acceleration;

        float bounciness;   // elasticity of collisions. 0 for inelastic, 1 for perfectly elastic
        float friction_s;
        float friction_d;
        float mass;
        float mass_inv;     // useful for calculations
    };
}
