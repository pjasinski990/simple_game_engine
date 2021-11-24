#include <cstring>

#include "renderer3d.h"
#include "../buffer/index_buffer.h"
#include "../renderable/drawable/drawable.h"
#include "../../../utils/logger.h"
#include "../../texture/texture.h"

namespace mrld
{
    Renderer3D::Renderer3D(const Shader *shader)
            : Renderer(shader)
            , _vbo_buffer_pointer{0}
            , _ibo_buffer_pointer{0}
    {
        _ibo = IndexBuffer::create_dynamic(MAX_INDICES);
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

    Renderer3D::~Renderer3D()
    {
        delete _vbo;
        delete _ibo;
    }

    Renderer3D::Renderer3D(Renderer3D &&o)
            : Renderer(std::move(o))
    {
        *this = std::move(o);
    }

    Renderer3D &Renderer3D::operator=(Renderer3D &&o)
    {
        _vbo = o._vbo;
        _ibo = o._ibo;
        o._vbo = nullptr;
        o._ibo = nullptr;
        return *this;
    }

    void Renderer3D::begin() const
    {
        _vbo->bind();
        _ibo->bind();
    }

    void Renderer3D::end() const
    {
        _vbo->unbind();
        _ibo->unbind();
    }

    void Renderer3D::submit(Drawable &d)
    {
        VertexData *vertices = d.get_vertices();
        const uint32_t n_vertices = d.get_vertices_count();
        const uint16_t *indices = d.get_indices();
        const uint32_t n_indices = d.get_indices_count();

        const Texture *tex = d.get_texture();
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
                for (uint32_t i = 0; i < d.get_vertices_count(); ++i) {
                    vertices[i].tex_slot = texture_slot;
                }
            }
        }

        // Transform positions according to the transform stack
        std::vector<vec3> old_positions;
        old_positions.reserve(d.get_vertices_count());
        if (has_transforms_on_stack()) {
            const mat4 &last_transform = get_last_transform();
            for (uint32_t i = 0; i < d.get_vertices_count(); ++i) {
                old_positions[i] = vertices[i].position;
                vertices[i].position = last_transform * vertices[i].position;
            }
        }

        // TODO handle size is bigger than the buffer itself
        uint32_t size = d.get_vertices_count() * VERTEX_SIZE;
        if (_vbo_buffer_pointer + size > BUFFER_SIZE) {
            Logger::log(LogLevel::DBG, "Performing early flush of Renderer2D batch (reached buffer size)");
            flush();
        }

        // todo optimize
        uint32_t size_i = n_indices * sizeof(uint16_t);
        if ((_ibo_buffer_pointer + size_i) * sizeof(uint16_t) > MAX_INDICES) {
            Logger::log(LogLevel::DBG, "Performing early flush of Renderer2D batch (reached max indices)");
            flush();
        }

        glBufferSubData(
                GL_ARRAY_BUFFER,
                _vbo_buffer_pointer,
                size,
                vertices
        );
        Logger::log(LogLevel::DBG, "Submitted %u bytes of vertex data at offset %u", size, _vbo_buffer_pointer);

        uint16_t *indices_copy = new uint16_t[n_indices];
        memcpy(indices_copy, indices, size_i);
        if (_ibo_buffer_pointer > 0) {
            uint32_t indices_offset = _vbo_buffer_pointer / VERTEX_SIZE;
            for (uint32_t i = 0; i < n_indices; ++i) {
                indices_copy[i] += indices_offset;
            }
        }
        glBufferSubData(
                GL_ELEMENT_ARRAY_BUFFER,
                _ibo_buffer_pointer,
                size_i,
                indices_copy
        );
        Logger::log(LogLevel::DBG, "Submitted %u bytes of index data at offset %u", size_i, _ibo_buffer_pointer);
        delete[] indices_copy;

        _vbo_buffer_pointer += size;
        _ibo_buffer_pointer += size_i;

        // Restore transformed positions
        // This way is faster than copying entire vertex data and altering the copy
        if (has_transforms_on_stack()) {
            for (uint32_t i = 0; i < d.get_vertices_count(); ++i) {
                vertices[i].position = old_positions[i];
            }
        }
    }

    void Renderer3D::flush()
    {
        Logger::log(LogLevel::DBG, "Flushing renderer batch, vertices size=%u, indices size=%u",
                    _vbo_buffer_pointer, _ibo_buffer_pointer);

        for (const auto &val: _texture_id_to_texture_slot) {
            glActiveTexture(GL_TEXTURE0 + val.second);
            glBindTexture(GL_TEXTURE_2D, val.first);
        }

        _vao.bind();
        _ibo->bind();
        glDrawElements(GL_TRIANGLES, _ibo_buffer_pointer / sizeof(uint16_t), GL_UNSIGNED_SHORT, nullptr);
        _ibo->unbind();
        _vao.unbind();
        _vbo_buffer_pointer = 0u;
        _ibo_buffer_pointer = 0u;
        _texture_id_to_texture_slot.clear();
    }
}
