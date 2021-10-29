#include <glad/glad.h>

#include "mrld/logger.h"
#include "mrld/attrib_data_buffer.h"
#include "mrld/vertex_array.h"

namespace mrld
{
    VertexArray::VertexArray()
    {
        GLuint gl_id;
        glGenVertexArrays(1, &gl_id);
        _id = gl_id;
    }

    VertexArray::~VertexArray()
    {
        for (AttribDataBuffer *q : _buffers) {
            delete q;
        }
    }

    void VertexArray::add_buffer(AttribDataBuffer *buffer, uint32_t attrib_location)
    {
        _buffers.push_back(buffer);
        bind();
        buffer->bind();
        glEnableVertexAttribArray(attrib_location);
        glVertexAttribPointer(attrib_location, buffer->get_attrib_element_count(), GL_FLOAT, GL_FALSE, 0, nullptr);
        buffer->unbind();
        unbind();
    }

    void VertexArray::bind() const
    {
        if (_id == 0) {
            Logger::log(LogLevel::WRN, "%s", "Warning: trying to bind b vertex array with ID = 0");
        }
        glBindVertexArray(_id);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    VertexArray &VertexArray::operator=(VertexArray &&o)
    {
        _id = o._id;
        _buffers = std::move(o._buffers);
        return *this;
    }

    VertexArray::VertexArray(VertexArray &&o)
    {
        *this = std::move(o);
    }
}
