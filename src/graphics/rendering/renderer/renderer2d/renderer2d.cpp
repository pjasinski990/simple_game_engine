#include <glad/glad.h>

#include "../renderable.h"
#include "sprite.h"
#include "renderer2d.h"
#include "../../../../utils/logger.h"

#define member_floats_count(type, member) (sizeof(((type*)0)->member) / sizeof(float))

namespace mrld
{
    Renderer2D::Renderer2D()
    : _sprites_submitted{0}
    {
        uint16_t *indices = new uint16_t [MAX_INDICES];
        for (uint16_t i = 0; i < MAX_SPRITES; ++i) {
            indices[i * 6 + 0] = i * 4 + 0;
            indices[i * 6 + 1] = i * 4 + 1;
            indices[i * 6 + 2] = i * 4 + 2;
            indices[i * 6 + 3] = i * 4 + 2;
            indices[i * 6 + 4] = i * 4 + 3;
            indices[i * 6 + 5] = i * 4 + 0;
        }
        _ibo = IndexBuffer::create_static(indices, MAX_INDICES);
        delete[] indices;

        _vbo = AttribDataBuffer::create_dynamic(
                BUFFER_SIZE,
                sizeof(VertexData) / sizeof(float)
                );

        _vao.bind();
        _vbo->bind();
        glVertexAttribPointer(ATTRIB_INDEX_POSITION, member_floats_count(VertexData, position), GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) offsetof(VertexData, position));
        glVertexAttribPointer(ATTRIB_INDEX_NORMAL, member_floats_count(VertexData, normal), GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) offsetof(VertexData, normal));
        glVertexAttribPointer(ATTRIB_INDEX_TEX_COORD, member_floats_count(VertexData, tex_coord), GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) offsetof(VertexData, tex_coord));
        glVertexAttribPointer(ATTRIB_INDEX_TEX_INDEX, member_floats_count(VertexData, tex_index), GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) offsetof(VertexData, tex_index));
        glVertexAttribPointer(ATTRIB_INDEX_COLOR, sizeof(uint32_t), GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const void*) offsetof(VertexData, color));
        glEnableVertexAttribArray(ATTRIB_INDEX_POSITION);
        glEnableVertexAttribArray(ATTRIB_INDEX_NORMAL);
        glEnableVertexAttribArray(ATTRIB_INDEX_TEX_COORD);
        glEnableVertexAttribArray(ATTRIB_INDEX_TEX_INDEX);
        glEnableVertexAttribArray(ATTRIB_INDEX_COLOR);
        _vbo->unbind();
        _vao.unbind();

        _transform_stack.push_back(mat4::identity());
        _last_transform = &_transform_stack.back();
    }

    Renderer2D::~Renderer2D()
    {
        delete _vbo;
        delete _ibo;
    }

    void Renderer2D::begin() const
    {
        _vbo->bind();
    }

    void Renderer2D::end() const
    {
        _vbo->unbind();
    }

    void Renderer2D::submit(const Renderable &r)
    {
        r.submit(*this);
    }

    void Renderer2D::flush()
    {
        Logger::log(LogLevel::DBG, "Flushing renderer batch N=%d", _sprites_submitted);
        _vao.bind();
        _ibo->bind();
        glDrawElements(GL_TRIANGLES, _sprites_submitted * 6, GL_UNSIGNED_SHORT, nullptr);
        _ibo->unbind();
        _vao.unbind();
        _sprites_submitted = 0;
    }

    void Renderer2D::push(const mat4 &transform, bool override /* = false */)
    {
        if (override) {
            _transform_stack.push_back(transform);
        }
        else {
            _transform_stack.push_back(_transform_stack.back() * transform);
        }
        _last_transform = &_transform_stack.back();
    }

    void Renderer2D::pop()
    {
        if (_transform_stack.size() > 1) {
            _transform_stack.pop_back();
            _last_transform = &_transform_stack.back();
        }
        else {
            Logger::log(LogLevel::WRN, "Trying to pop nonexistent transformation from "
                                       "transformation stack in Renderer2D");
        }
    }

    void Renderer2D::submit_data(const void *data, uint32_t size)
    {
        if (size != SPRITE_SIZE) {
            Logger::log(LogLevel::ERR, "Submitted wrong size of renderable to Renderer2D");
        }

        glBufferSubData(
                GL_ARRAY_BUFFER,
                SPRITE_SIZE * _sprites_submitted,
                size,
                data
        );

        Logger::log(LogLevel::DBG, "Submitted %u bytes of vertex data. "
                                   "N submitted sprites: %u", size, _sprites_submitted);

        if (++_sprites_submitted > MAX_SPRITES) {
            Logger::log(LogLevel::DBG, "Performing early flush of Renderer2D batch (reached buffer size)");
            flush();
        }
    }
}
