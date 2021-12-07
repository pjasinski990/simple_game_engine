#include <cstring>

#include "renderer3d.h"
#include "../buffer/index_buffer.h"
#include "../renderable/drawable/drawable.h"
#include "../../../utils/logger.h"
#include "../../texture/texture.h"

namespace mrld
{
    Renderer3D::Renderer3D(Shader *shader)
            : Renderer(shader)
            , _n_submitted_vertices{0}
            , _n_submitted_indices{0}
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
        _shader->use();
        _vbo->bind();
        _ibo->bind();
    }

    void Renderer3D::end() const
    {
        _ibo->unbind();
        _vbo->unbind();
        _shader->disable();
    }

    void Renderer3D::submit(Drawable &d)
    {
        VertexData *vertices = d.get_vertices();
        const uint32_t n_vertices = d.get_vertices_count();
        const uint16_t *indices = d.get_indices();
        const uint32_t n_indices = d.get_indices_count();

        const Texture *tex = d.get_texture();
        if (tex) {
            // Set texture slots in vertices - they can't be initially set in sprite,
            // as the texture slot is provided by the renderer and is dynamic.
            float texture_slot = static_cast<float>(retrieve_texture_slot(tex->get_id()));
            if (texture_slot == -1.0f) {
                Logger::log(LogLevel::WRN, "Could not find texture slot for model - skipping rendering");
                end();
                return;
            }
            for (uint32_t i = 0; i < n_vertices; ++i) {
                vertices[i].tex_slot = texture_slot;
            }
        }

        // Transform positions according to the transform stack
        // Models own model matrix should be pushed before submitting
        _shader->set_mat4("model_matrix", *_last_transform);

        uint32_t size = n_vertices * VERTEX_SIZE;
        uint32_t size_i = n_indices * sizeof(uint16_t);
        if (size > BUFFER_SIZE) {
            Logger::log(LogLevel::WRN, "Not rendering passed model - vertices size is too large for the buffer");
            return;
        }
        if (n_indices > MAX_INDICES) {
            Logger::log(LogLevel::WRN, "Not rendering passed model - indices size is too large for the buffer");
            return;
        }

        glBufferSubData(GL_ARRAY_BUFFER, 0u, size, vertices);
        Logger::log(LogLevel::DBG, "Submitted %u bytes of vertex data", size);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0u, size_i, indices);
        Logger::log(LogLevel::DBG, "Submitted %u bytes of index data", size_i);
        _n_submitted_vertices += n_vertices;
        _n_submitted_indices += n_indices;
        flush();
    }

    void Renderer3D::flush()
    {
        Logger::log(LogLevel::DBG, "Flushing renderer batch, vertices count=%u, indices count=%u",
                    _n_submitted_vertices, _n_submitted_indices);
        for (const auto &val: _texture_id_to_texture_slot) {
            glActiveTexture(GL_TEXTURE0 + val.second);
            glBindTexture(GL_TEXTURE_2D, val.first);
        }

        _vao.bind();
        _ibo->bind();
        glDrawElements(GL_TRIANGLES, _n_submitted_indices, GL_UNSIGNED_SHORT, nullptr);
        _ibo->unbind();
        _vao.unbind();
        _n_submitted_vertices = 0u;
        _n_submitted_indices = 0u;
        _texture_id_to_texture_slot.clear();
    }
}
