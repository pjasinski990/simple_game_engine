#include <glad/glad.h>

#include <mrld/attrib_data_buffer.h>
#include <mrld/logger.h>

namespace mrld
{
    AttribDataBuffer::AttribDataBuffer(float *data, uint32_t n_values, uint32_t attrib_element_count):
    _attrib_element_count{attrib_element_count}
    {
        GLuint gl_id;
        glGenBuffers(1, &gl_id);
        _id = gl_id;

        bind();
        glBufferData(GL_ARRAY_BUFFER, n_values * sizeof(float), data, GL_STATIC_DRAW);
        unbind();
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
