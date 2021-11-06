#include "../../../../math/vec3.h"
#include "../../../../math/vec2.h"
#include "sprite.h"
#include "renderer2d.h"

namespace mrld
{
    Sprite::Sprite(const vec3 &position, const vec2 &size, const vec4 &color, uint32_t z_index /* =0 */, uint32_t tex_index /* =0 */)
    : _position{position}
    , _size {size}
    , _color(color)
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

        uint8_t r = static_cast<uint32_t>(_color.x * 255.0f);
        uint8_t g = static_cast<uint32_t>(_color.y * 255.0f);
        uint8_t b = static_cast<uint32_t>(_color.z * 255.0f);
        uint8_t a = static_cast<uint32_t>(_color.w * 255.0f);
        uint32_t ui_color = a << 24 | b << 16 | g << 8 | r;

        sprite[0] = {
                last_transform * vec3(x, y, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 0.0f),
                tex_index,
                ui_color
        };
        sprite[1] = {
                last_transform * vec3(x + width, y, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 0.0f),
                tex_index,
                ui_color
        };
        sprite[2] = {
                last_transform * vec3(x + width, y + height, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 1.0f),
                tex_index,
                ui_color
        };
        sprite[3] = {
                last_transform * vec3(x, y + height, 0.0f),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 1.0f),
                tex_index,
                ui_color
        };
        renderer.submit_data(sprite, sizeof(VertexData) * 4);
    }
}
