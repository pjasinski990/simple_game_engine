#pragma once

#include "../../buffer/vertex_data.h"
#include "../../buffer/vertex_array.h"
#include "../../buffer/index_buffer.h"
#include "../../../shader/shader.h"
#include "../../group/group2d.h"

namespace mrld
{
    class Renderable;
    class Renderer2D
    {
    public:
        Renderer2D();
        ~Renderer2D();

        void begin() const;
        void end() const;
        void submit(const Renderable &o);
        void flush();

        void push(const mat4 &transform, bool override = false);
        void pop();

        void submit_data(const void* data, uint32_t size);
        const mat4 &get_last_transform() const { return *_last_transform; }

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
        std::vector<mat4> _transform_stack;
        const mat4 *_last_transform;
        uint32_t _sprites_submitted;
    };
}
