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
        Model(VertexData *vertices, uint32_t v_count, const Texture *tex = nullptr);

        void submit_self(Renderer &r) override;
        VertexData* get_vertices() override { return _vertices.data(); }
        uint32_t get_vertices_count() const override { return _v_count; }
        const uint16_t* get_indices() const override { return _indices.data(); }
        uint32_t get_indices_count() const override { return _i_count; }

        inline void translate(const vec3 &o) { _model_matrix = mat4::translate(o) * _model_matrix; };
        inline void scale(const vec3 &o) { _model_matrix = mat4::scale(o) * _model_matrix; };
        void rotate(const vec3 &axis, float angle_rads);

        void set_model_matrix(const mat4 &o) { _model_matrix = o; }
        const mat4& get_model_matrix() const { return _model_matrix; }

    protected:

    private:
        mat4 _model_matrix;
        uint32_t _v_count;
        uint32_t _i_count;
    };
}
