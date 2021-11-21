#pragma once

#include <vector>

#include "renderable.h"
#include "../../../math/quaternion.h"
#include "../buffer/vertex_data.h"

namespace mrld
{
    class Texture;
    class Model: public Renderable
    {
    public:
        Model(VertexData *vertices, uint32_t count);
        void submit(Renderer &renderer) const override;
    private:
        std::vector<VertexData> _vertices;

        vec3 _position;
        vec3 _scale;
        quat _rotation;
        const Texture *_texture;
    };
}
