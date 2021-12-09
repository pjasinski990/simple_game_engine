#pragma once

#include "../../math/vec3.h"

namespace mrld
{
    struct point_light
    {
        vec3 position;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        float constant;
        float linear;
        float quadratic;
    };
}
