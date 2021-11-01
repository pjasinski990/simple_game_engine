#pragma once

#include <cstdint>

namespace mrld
{
    class AttribDataBuffer
    {
    public:
        ~AttribDataBuffer();
        static AttribDataBuffer *create_static(float *data, uint32_t buffer_size, uint32_t attrib_element_count);
        static AttribDataBuffer *create_dynamic(uint32_t buffer_size, uint32_t attrib_element_count);

        void bind() const;
        void unbind() const;

        inline uint32_t get_attrib_element_count() const { return _attrib_element_count; }
        inline uint32_t get_id() const { return _id; }

    private:
        AttribDataBuffer(float *data, uint32_t buffer_size, uint32_t attrib_element_count, bool is_static);
        uint32_t _id;
        uint32_t _attrib_element_count;
    };
}
