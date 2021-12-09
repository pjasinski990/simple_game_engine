#pragma once

#include "renderer.h"
#include "../buffer/vertex_data.h"
#include "../buffer/vertex_array.h"
#include "../buffer/index_buffer.h"
#include "../../shader/shader.h"
#include "../renderable/group/group.h"

namespace mrld
{
    class Renderable;
    class Renderer2D: public Renderer
    {
    public:
        Renderer2D(Shader *shader);
        ~Renderer2D();
        Renderer2D(const Renderer2D &o) = delete;
        Renderer2D& operator=(const Renderer2D &o) = delete;
        Renderer2D(Renderer2D &&o);
        Renderer2D& operator=(Renderer2D &&o);

        void begin() const override;
        void end() const override;
        using Renderer::submit;
        void submit(Drawable &o) override;
        void flush() override;

    private:
        const uint32_t MAX_SPRITES = 8192u;
        const uint32_t SPRITE_SIZE = VERTEX_SIZE * 4;
        const uint32_t BUFFER_SIZE = MAX_SPRITES * SPRITE_SIZE;
        const uint32_t MAX_INDICES = MAX_SPRITES * 6;

        VertexArray _vao;
        AttribDataBuffer *_vbo;
        IndexBuffer *_ibo;
        uint32_t _sprites_submitted;
    };
}
