#pragma once

#include "../../math/vec3.h"

namespace mrld
{
    struct directional_light
    {
        vec3 direction;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
}
