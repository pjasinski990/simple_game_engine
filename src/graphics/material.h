#pragma once

#include "../math/vec3.h"

namespace mrld
{
    struct material {
        material()
        : ambient{vec3(1.0f, 1.0f, 1.0f)}
        , diffuse{vec3(1.0f, 1.0f, 1.0f)}
        , specular{vec3(1.0f, 1.0f, 1.0f)}
        , specular_e{32.0f}
        , dissolve{0.0f}
        {
            /* no-op */
        }

        std::string name;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float specular_e;
        float dissolve;
    };
}