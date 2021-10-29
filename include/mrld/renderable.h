#pragma once

#include <vector>

#include "shader.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "mat4.h"

namespace mrld
{
    class Renderable
    {
    public:
        virtual ~Renderable() = default;
        Renderable() = default;
        Renderable(const Shader *shader)
            : _shader{shader}
        { }

        virtual void transform() const {}

        inline const Shader &get_shader() const { return *_shader; }
        inline const VertexArray &get_vao() const { return _vao; }
        inline const IndexBuffer &get_ibo() const { return _ibo; }
    protected:
        VertexArray _vao;
        IndexBuffer _ibo;
        const Shader *_shader;
    };
}
