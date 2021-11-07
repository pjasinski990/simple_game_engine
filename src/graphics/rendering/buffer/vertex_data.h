#pragma once

#include "../../../math/vec3.h"
#include "../../../math/vec4.h"
#include "../../../math/vec2.h"

namespace mrld
{
    struct VertexData
    {
        vec3 position;
        vec3 normal;
        vec2 tex_coord;
        float tex_slot;
        uint32_t color;
    };
}
