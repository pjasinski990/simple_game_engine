#include "renderable2d.h"

namespace mrld
{
    Renderable2D::Renderable2D(const vec2 &position, const vec2 &size, const vec4 &color, uint32_t z_index /* =0 */, uint32_t tex_index /* =0 */)
    : _position {position}
    , _size {size}
    , _color {color}
    , _z_index {z_index}
    , _tex_index {tex_index}
    { }

    Renderable2D::~Renderable2D()
    { }
}
