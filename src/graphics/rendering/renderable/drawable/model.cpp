#include "model.h"
#include "../../../texture/texture.h"

namespace mrld
{
    Model::Model(VertexData *vertices, uint32_t v_count, uint16_t *indices, uint32_t i_count, const Texture *tex /* = nullptr */)
    : Drawable(tex)
    , _model_matrix{mat4::identity()}
    , _v_count{v_count}
    , _i_count{i_count}
    {
        _vertices.reserve(_v_count);
        for (uint32_t i = 0; i < _v_count; ++i) {
            _vertices.push_back(vertices[i]);
        }
        _indices.reserve(_i_count);
        for (uint32_t i = 0; i < _i_count; ++i) {
            _indices.push_back(indices[i]);
        }
    }

    void Model::submit(Renderer &r)
    {
        r.push(_model_matrix);
        r.submit(*this);
        r.pop();
    }
}
