#pragma once

#include <cstdint>

namespace mrld
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        IndexBuffer(uint16_t *data, uint32_t n);
        void bind() const;
        void unbind() const;
        inline uint32_t get_count() const { return _count; }
    private:
        uint32_t _id;
        uint32_t _count;
    };
}
