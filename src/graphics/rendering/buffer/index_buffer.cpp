#include <glad/glad.h>

#include "index_buffer.h"
#include "../../../utils/logger.h"

namespace mrld
{
    IndexBuffer::IndexBuffer(uint16_t *data, uint32_t n, bool is_static):
    _count{n}
    {
        GLuint gl_id;
        glGenBuffers(1, &gl_id);
        _id = gl_id;

        bind();
        if (is_static) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, n * sizeof(uint16_t), data, GL_STATIC_DRAW);
        }
        else {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, n * sizeof(uint16_t), data, GL_DYNAMIC_DRAW);
        }
        unbind();
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &_id);
    }

    IndexBuffer* IndexBuffer::create_static(uint16_t *data, uint32_t n_indices)
    {
        IndexBuffer *o = new IndexBuffer(data, n_indices, true);
        return o;
    }

    IndexBuffer* IndexBuffer::create_dynamic(uint32_t n_indices)
    {
        IndexBuffer *o = new IndexBuffer(nullptr, n_indices, false);
        return o;
    }

    void IndexBuffer::bind() const
    {
        if (_id == 0) {
            Logger::log(LogLevel::WRN, "%s", "Warning: trying to bind a buffer with ID = 0");
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
