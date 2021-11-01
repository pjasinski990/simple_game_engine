#include <glad/glad.h>

#include "attrib_data_buffer.h"
#include "../../../utils/logger.h"
#include <iostream>

namespace mrld
{
    AttribDataBuffer::AttribDataBuffer(float *data, uint32_t buffer_size, uint32_t attrib_element_count, bool is_static):
    _attrib_element_count{attrib_element_count}
    {
        GLuint gl_id;
        glGenBuffers(1, &gl_id);
        _id = gl_id;

        bind();
        if (is_static) {
            Logger::log(LogLevel::DBG, "Allocating static array buffer - SIZE: %u", buffer_size);
            glBufferData(GL_ARRAY_BUFFER, buffer_size, data, GL_STATIC_DRAW);
        } else {
            Logger::log(LogLevel::DBG, "Allocating dynamic array buffer - SIZE: %u", buffer_size);
            glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_DYNAMIC_DRAW);
        }
        unbind();
    }

    AttribDataBuffer::~AttribDataBuffer()
    {
        glDeleteBuffers(1, &_id);
    }

    AttribDataBuffer *AttribDataBuffer::create_static(float *data, uint32_t buffer_size, uint32_t attrib_element_count)
    {
        AttribDataBuffer *o = new AttribDataBuffer(data, buffer_size, attrib_element_count, true);
        return o;
    }

    AttribDataBuffer *AttribDataBuffer::create_dynamic(uint32_t buffer_size, uint32_t attrib_element_count)
    {
        AttribDataBuffer *o = new AttribDataBuffer(nullptr, buffer_size, attrib_element_count, false);
        return o;
    }

    void AttribDataBuffer::bind() const
    {
        if (_id == 0) {
            Logger::log(LogLevel::WRN, "%s", "Warning: trying to bind a buffer with ID = 0");
        }
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void AttribDataBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
