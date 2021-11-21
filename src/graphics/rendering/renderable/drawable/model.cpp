#include "model.h"
#include "../../../texture/texture.h"

namespace mrld
{
    Model::Model(VertexData *vertices, uint32_t count)
            : _vertices{}
            , _position{vec3()}
            , _scale{vec3()}
            , _rotation{quat()}
    {
        _vertices.reserve(count);
        for (uint32_t i = 0; i < count; ++i) {
            _vertices.push_back(vertices[i]);
        }
    }

    void Model::submit(Renderer &renderer) const
    {

    }
}
