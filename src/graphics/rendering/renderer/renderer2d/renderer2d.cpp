#include <glad/glad.h>

#include "renderable2d.h"
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
        glVertexAttribPointer(ATTRIB_INDEX_POSITION, member_floats_count(VertexData, position), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*) offsetof(VertexData, position));
        glVertexAttribPointer(ATTRIB_INDEX_NORMAL, member_floats_count(VertexData, normal), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*) offsetof(VertexData, normal));
        glVertexAttribPointer(ATTRIB_INDEX_TEX_COORD, member_floats_count(VertexData, tex_coord), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*) offsetof(VertexData, tex_coord));
        glVertexAttribPointer(ATTRIB_INDEX_TEX_INDEX, member_floats_count(VertexData, tex_index), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*) offsetof(VertexData, tex_index));
        glVertexAttribPointer(ATTRIB_INDEX_COLOR, member_floats_count(VertexData, color), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*) offsetof(VertexData, color));
        glEnableVertexAttribArray(ATTRIB_INDEX_POSITION);
        glEnableVertexAttribArray(ATTRIB_INDEX_NORMAL);
        glEnableVertexAttribArray(ATTRIB_INDEX_TEX_COORD);
        glEnableVertexAttribArray(ATTRIB_INDEX_TEX_INDEX);
        glEnableVertexAttribArray(ATTRIB_INDEX_COLOR);
        _vbo->unbind();
        _vao.unbind();
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

    void Renderer2D::submit(const Renderable2D &o)
    {
        VertexData sprite[4];
        const float x = o.get_position().x;
        const float y = o.get_position().y;
        const float z = static_cast<float>(o.get_z_index());
        const float width = o.get_size().x;
        const float height = o.get_size().y;
        const float tex_index = static_cast<float>(o.get_tex_index());
        sprite[0] = {
                vec3(x, y, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 0.0f),
                tex_index,
                o.get_color()
                };
        sprite[1] = {
                vec3(x + width, y, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 0.0f),
                tex_index,
                o.get_color()
        };
        sprite[2] = {
                vec3(x + width, y + height, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 1.0f),
                tex_index,
                o.get_color()
        };
        sprite[3] = {
                vec3(x, y + height, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 1.0f),
                tex_index,
                o.get_color()
        };

        glBufferSubData(
                GL_ARRAY_BUFFER,
                SPRITE_SIZE * _sprites_submitted,
                SPRITE_SIZE,
                (const void*) &sprite
                );
        ++_sprites_submitted;

        Logger::log(LogLevel::DBG, "Submitted sprite N=%d", _sprites_submitted);
        if (_sprites_submitted == MAX_SPRITES) {
            Logger::log(LogLevel::DBG, "Performing early flush of Renderer2D batch (reached max sprites)");
            flush();
        }
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

}
