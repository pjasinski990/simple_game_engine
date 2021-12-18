#pragma once

#include "../../math/vec3.h"

namespace mrld
{
    struct material {
        material() = default;

        material(const vec3 &ambient, const vec3 &diffuse, const vec3 &specular, float specular_e, float dissolve, const std::string &name)
        : ambient{ambient}
        , diffuse{diffuse}
        , specular{specular}
        , specular_e{specular_e}
        , dissolve{dissolve}
        , name{name}
        {
            /* no-op */
        }

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float specular_e;
        float dissolve;
        std::string name;
    };

    namespace materials
    {
        static material basic {
            vec3(1.0f),
            vec3(1.0f),
            vec3(1.0f),
            1.0f,
            1.0f,
            std::string("base")
        };

        static material emerald {
                vec3(0.0215f, 0.1745f, 0.0215f),
                vec3(0.07568f,	0.61424f, 0.07568f ),
                vec3(0.633f, 0.727811f, 0.633f),
                76.8f,
                1.0f,
                std::string("emerald")
        };
        static material red_plastic {
            vec3(0.0f),
            vec3(0.5f, 0.0f, 0.0f),
            vec3(0.7f, 0.6f, 0.6f),
            32.0f,
            1.0f,
            std::string("red_plastic")
        };
        static material yellow_rubber {
                vec3(0.05f, 0.05f, 0.0f),
                vec3(0.5f, 0.5f, 0.4f),
                vec3(0.7f, 0.7f, 0.04f),
                10.0f,
                1.0f,
                std::string("yellow_rubber")
        };
    }
}