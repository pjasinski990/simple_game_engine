#pragma once

#include <cstdint>

namespace mrld
{
    class AttribDataBuffer
    {
    public:
        AttribDataBuffer(float *data, uint32_t n_values, uint32_t attrib_element_count);
        void bind() const;
        void unbind() const;
        inline uint32_t get_attrib_element_count() const { return _attrib_element_count; }
    private:
        uint32_t _id;
        uint32_t _attrib_element_count;
    };
}
