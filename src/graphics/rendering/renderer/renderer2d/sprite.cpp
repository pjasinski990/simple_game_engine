#include "../../../../math/vec3.h"
#include "../../../../math/vec2.h"
#include "sprite.h"
#include "renderer2d.h"

namespace mrld
{
    Sprite::Sprite(const vec3 &position, const vec2 &size, const vec4 &color, uint32_t z_index /* =0 */, uint32_t tex_index /* =0 */)
    : _position{position}
    , _size {size}
    // TODO represent color as uint32
    , _color {color}
    , _z_index {z_index}
    , _tex_index {tex_index}
    { }

    void Sprite::submit(Renderer2D &renderer) const
    {
        // TODO render with z-index depth
        VertexData sprite[4];
        const mat4 &last_transform = renderer.get_last_transform();
        const float x = _position.x;
        const float y = _position.y;
        const float width = _size.x;
        const float height = _size.y;
        const float tex_index = static_cast<float>(_tex_index);
        sprite[0] = {
                last_transform * vec3(x, y, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 0.0f),
                tex_index,
                get_color()
        };
        sprite[1] = {
                last_transform * vec3(x + width, y, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 0.0f),
                tex_index,
                get_color()
        };
        sprite[2] = {
                last_transform * vec3(x + width, y + height, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 1.0f),
                tex_index,
                get_color()
        };
        sprite[3] = {
                last_transform * vec3(x, y + height, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 1.0f),
                tex_index,
                get_color()
        };
        renderer.submit_data(sprite, sizeof(VertexData) * 4);
    }
}
