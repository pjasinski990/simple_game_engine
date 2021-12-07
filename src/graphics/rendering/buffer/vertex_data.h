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
        float material_slot;
        uint32_t color;

        friend std::ostream& operator<<(std::ostream& out, const VertexData& o);
    };

    inline std::ostream& operator<<(std::ostream& out, const VertexData& o) {
        out << o.position << std::endl << o.normal << std::endl << o.tex_coord << std::endl << o.tex_slot << std::endl << o.color << std::endl;
        return out;
    }
}
