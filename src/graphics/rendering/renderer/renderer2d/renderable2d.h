#pragma once

#include <vector>
#include "../../../../math/vec2.h"
#include "../../../../math/vec4.h"

namespace mrld
{
    class Renderable2D
    {
    public:
        Renderable2D(const vec2 &position, const vec2 &size, const vec4 &color, uint32_t z_index = 0, uint32_t tex_index = 0);
        ~Renderable2D();

        inline vec2 get_position() const { return _position; }
        inline vec2 get_size() const { return _size; }
        inline vec4 get_color() const { return _color; }
        inline uint32_t get_z_index() const { return _z_index; }
        inline uint32_t get_tex_index() const { return _tex_index; }

        inline void set_position(const vec2 &position) { _position = position; }
        inline void set_size(const vec2 &size) { _size = size; }
        inline void set_color(const vec4 &color) { _color = color; }
    private:
        vec2 _position;
        vec2 _size;
        vec4 _color;
        uint32_t _z_index;
        uint32_t _tex_index;
    };
}
