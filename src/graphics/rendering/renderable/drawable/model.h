#pragma once

#include <vector>

#include "../../renderer/renderer.h"
#include "../../../../math/quaternion.h"
#include "../../buffer/vertex_data.h"
#include "drawable.h"

namespace mrld
{
    class Texture;
    class Model: public Drawable
    {
    public:
        Model(VertexData *vertices, uint32_t v_count, uint16_t *indices, uint32_t i_count, const Texture *tex = nullptr);
        VertexData* get_vertices() override { return _vertices.data(); }
        uint32_t get_vertices_count() const override { return _v_count; }
        const uint16_t* get_indices() const override { return _indices.data(); }
        uint32_t get_indices_count() const override { return _i_count; }

    private:
        mat4 _model_matrix;
        uint32_t _v_count;
        uint32_t _i_count;
    };
}
