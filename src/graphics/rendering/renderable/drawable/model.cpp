#include "model.h"
#include "../../../texture/texture.h"
#include "../../../../utils/logger.h"

namespace mrld
{
    Model::Model(
            VertexData *vertices,
            uint32_t v_count,
            uint16_t *indices,
            uint32_t i_count,
            const Texture *tex /* = nullptr */)
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

    Model::Model(VertexData *vertices,
                 uint32_t v_count,
                 const Texture *tex)
    : Drawable(tex)
    , _model_matrix{mat4::identity()}
    , _v_count{v_count}
    , _i_count{v_count}
    {
        _vertices.reserve(_v_count);
        for (uint32_t i = 0; i < _v_count; ++i) {
            _vertices.push_back(vertices[i]);
        }
        _indices.reserve(_i_count);
        uint32_t k = 0;
        for (uint32_t i = 0; i < _i_count; ++i) {
            _indices.push_back(k++);
        }
    }

    void Model::submit_self(Renderer &r)
    {
        r.push(_model_matrix);
        r.submit(*this);
        r.pop();
    }

    void Model::rotate(const vec3 &axis, float angle_rads)
    {
        quat q(axis, angle_rads);
        _model_matrix = q.create_rotation_matrix() * _model_matrix;
    }
}
