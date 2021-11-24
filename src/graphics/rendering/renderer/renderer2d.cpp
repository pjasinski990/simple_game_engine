#include <glad/glad.h>

#include "../renderable/renderable.h"
#include "../renderable/drawable/sprite.h"
#include "renderer2d.h"
#include "../../../utils/logger.h"

namespace mrld
{
    Renderer2D::Renderer2D(Shader *shader)
    : Renderer(shader)
    , _sprites_submitted{0}
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
        glVertexAttribPointer(ATTRIB_INDEX_TEX_SLOT, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) offsetof(VertexData, tex_slot));
        glVertexAttribPointer(ATTRIB_INDEX_COLOR, sizeof(uint32_t), GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const void*) offsetof(VertexData, color));
        glEnableVertexAttribArray(ATTRIB_INDEX_POSITION);
        glEnableVertexAttribArray(ATTRIB_INDEX_NORMAL);
        glEnableVertexAttribArray(ATTRIB_INDEX_TEX_COORD);
        glEnableVertexAttribArray(ATTRIB_INDEX_TEX_SLOT);
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

    Renderer2D::Renderer2D(Renderer2D &&o)
            : Renderer(std::move(o))
    {
        *this = std::move(o);
    }

    Renderer2D &Renderer2D::operator=(Renderer2D &&o)
    {
        _vbo = o._vbo;
        _ibo = o._ibo;
        o._vbo = nullptr;
        o._ibo = nullptr;
        return *this;
    }

    void Renderer2D::begin() const
    {
        _vbo->bind();
    }

    void Renderer2D::end() const
    {
        _vbo->unbind();
    }

    void Renderer2D::submit(Drawable &r)
    {
        VertexData *vertices = r.get_vertices();

        const Texture *tex = r.get_texture();
        if (tex) {
            // Set texture slots in vertices if hasn't been set yet or changed - they can't be initially
            // set in sprite, as the texture slot is provided by the renderer and is dynamic.
            float texture_slot = static_cast<float>(retrieve_texture_slot(tex->get_id()));
            if (texture_slot == -1.0f) {
                Logger::log(LogLevel::DBG, "Performing early flush - no empty texture slots.");
                end();
                flush();
                begin();
                texture_slot = static_cast<float>(retrieve_texture_slot(tex->get_id()));
            }

            if (vertices->tex_slot != texture_slot) {
                for (uint32_t i = 0; i < r.get_vertices_count(); ++i) {
                    vertices[i].tex_slot = texture_slot;
                }
            }
        }

        // Transform positions according to the transform stack
        std::vector<vec3> old_positions;
        old_positions.reserve(r.get_vertices_count());
        if (has_transforms_on_stack()) {
            const mat4 &last_transform = get_last_transform();
            for (uint32_t i = 0; i < r.get_vertices_count(); ++i) {
                old_positions[i] = vertices[i].position;
                vertices[i].position = last_transform * vertices[i].position;
            }
        }

        uint32_t size = r.get_vertices_count() * VERTEX_SIZE;
        if (size % SPRITE_SIZE) {
            Logger::log(LogLevel::WRN, "Submitted wrong size of renderable to Renderer2D");
        }
        glBufferSubData(
                GL_ARRAY_BUFFER,
                SPRITE_SIZE * _sprites_submitted,
                size,
                vertices
        );
        Logger::log(LogLevel::DBG, "Submitted %u bytes of vertex data. "
                                   "N submitted sprites: %u", size, _sprites_submitted);
        _sprites_submitted += size / SPRITE_SIZE;
        if (_sprites_submitted > MAX_SPRITES) {
            Logger::log(LogLevel::DBG, "Performing early flush of Renderer2D batch (reached buffer size)");
            flush();
        }

        // Restore transformed positions
        // Faster than copying entire vertex data and altering the copy
        if (has_transforms_on_stack()) {
            for (uint32_t i = 0; i < r.get_vertices_count(); ++i) {
                vertices[i].position = old_positions[i];
            }
        }
    }

    void Renderer2D::flush()
    {
        Logger::log(LogLevel::DBG, "Flushing renderer batch N=%d", _sprites_submitted);
        for (const auto &val: _texture_id_to_texture_slot) {
            glActiveTexture(GL_TEXTURE0 + val.second);
            glBindTexture(GL_TEXTURE_2D, val.first);
        }
        _vao.bind();
        _ibo->bind();
        glDrawElements(GL_TRIANGLES, _sprites_submitted * 6, GL_UNSIGNED_SHORT, nullptr);
        _ibo->unbind();
        _vao.unbind();
        _sprites_submitted = 0u;
        _texture_id_to_texture_slot.clear();
    }
}
