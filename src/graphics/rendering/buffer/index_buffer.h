#pragma once

#include <cstdint>

namespace mrld
{
    class IndexBuffer
    {
    public:
        static IndexBuffer* create_static(uint16_t *data, uint32_t n_indices);
        static IndexBuffer* create_dynamic(uint32_t n_indices);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;
        inline uint32_t get_count() const { return _count; }
    private:
        IndexBuffer(uint16_t *data, uint32_t n, bool is_static);
        uint32_t _id;
        uint32_t _count;
    };
}
