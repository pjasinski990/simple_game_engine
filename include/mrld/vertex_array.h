#pragma once

#include <vector>

#include "attrib_data_buffer.h"

namespace mrld
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        VertexArray& operator=(const VertexArray &o) = delete;
        VertexArray(const VertexArray &o) = delete;
        VertexArray& operator=(VertexArray &&o);
        VertexArray(VertexArray &&o);
        void bind() const;
        void unbind() const;
        void add_buffer(AttribDataBuffer *buffer, uint32_t id);
    private:
        std::vector <AttribDataBuffer*> _buffers;
        uint32_t _id;
    };
}
