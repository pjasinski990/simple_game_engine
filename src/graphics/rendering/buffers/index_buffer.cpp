#include <glad/glad.h>

#include "mrld/index_buffer.h"
#include "mrld/logger.h"

namespace mrld
{
    IndexBuffer::IndexBuffer():
    _count{0}
    { }

    IndexBuffer::IndexBuffer(uint16_t *data, uint32_t n):
    _count{n}
    {
        GLuint gl_id;
        glGenBuffers(1, &gl_id);
        _id = gl_id;

        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, n * sizeof(uint16_t), data, GL_STATIC_DRAW);
        unbind();
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
