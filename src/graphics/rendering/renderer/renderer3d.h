#pragma once

#include "renderer.h"
#include "../buffer/vertex_array.h"
#include "../../materials/material.h"

namespace mrld
{
    class AttribDataBuffer;
    class IndexBuffer;
    class Renderer3D: public Renderer
    {
    public:
        Renderer3D(Shader *shader);
        ~Renderer3D();
        Renderer3D(const Renderer3D &o) = delete;
        Renderer3D& operator=(const Renderer3D &o) = delete;
        Renderer3D(Renderer3D &&o);
        Renderer3D& operator=(Renderer3D &&o);

        void begin() const override;
        void end() const override;
        using Renderer::submit;
        void submit(Drawable &o) override;
        void flush() override;

    private:
        const uint32_t MAX_VERTICES = 65535u;
        const uint32_t MAX_INDICES = 131072u;
        const uint32_t BUFFER_SIZE = MAX_VERTICES * VERTEX_SIZE;

        VertexArray _vao;
        AttribDataBuffer *_vbo;
        IndexBuffer *_ibo;
        uint32_t _n_submitted_vertices;
        uint32_t _n_submitted_indices;
    };
}
