#pragma once

#include "../../buffer/vertex_data.h"
#include "../../buffer/vertex_array.h"
#include "../../buffer/index_buffer.h"
#include "../../../shader/shader.h"
#include "../../group/group2d.h"
#include "../renderer.h"

namespace mrld
{
    class Renderable;
    class Renderer2D: public Renderer
    {
    public:
        Renderer2D();
        ~Renderer2D();

        void begin() const override;
        void end() const override;

        void submit(const Renderable &o) override;
        void flush() override;

        void submit_data(const void* data, uint32_t size) override;

    private:
        constexpr static uint32_t MAX_SPRITES = 10000;
        constexpr static uint32_t VERTEX_SIZE = sizeof(VertexData);
        constexpr static uint32_t SPRITE_SIZE = VERTEX_SIZE * 4;
        constexpr static uint32_t BUFFER_SIZE = MAX_SPRITES * SPRITE_SIZE;
        constexpr static uint32_t MAX_INDICES = MAX_SPRITES * 6;

        constexpr static uint32_t ATTRIB_INDEX_POSITION = 0;
        constexpr static uint32_t ATTRIB_INDEX_NORMAL = 1;
        constexpr static uint32_t ATTRIB_INDEX_TEX_COORD = 2;
        constexpr static uint32_t ATTRIB_INDEX_TEX_INDEX = 3;
        constexpr static uint32_t ATTRIB_INDEX_COLOR = 4;

        VertexArray _vao;
        AttribDataBuffer *_vbo;
        IndexBuffer *_ibo;
        uint32_t _sprites_submitted;
    };
}
