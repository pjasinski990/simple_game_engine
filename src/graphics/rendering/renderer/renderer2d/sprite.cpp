#include "../../../../math/vec3.h"
#include "../../../../math/vec2.h"
#include "../../../../utils/logger.h"
#include "sprite.h"
#include "renderer2d.h"

namespace mrld
{
    Sprite::Sprite(const vec3 &position, const vec2 &size, const Texture *tex /* = nullptr */, const vec4 &color /* = color::BLACK */)
    : _position{position}
    , _size {size}
    , _color(color)
    , _texture{tex}
    { }

    void Sprite::submit(Renderer &renderer) const
    {
        VertexData sprite[4];
        const mat4 &last_transform = renderer.get_last_transform();
        const float x = _position.x;
        const float y = _position.y;
        const float z = _position.z;
        const float width = _size.x;
        const float height = _size.y;

        float texture_slot = -1.0f;
        uint32_t uint_color = 0;
        if (_texture) {
            texture_slot = static_cast<float>(renderer.retrieve_texture_slot(_texture->get_id()));
            if (texture_slot == -1.0f) {
                Logger::log(LogLevel::DBG, "Performing early flush - no empty texture slots.");
                renderer.end();
                renderer.flush();
                renderer.begin();
                texture_slot = static_cast<float>(renderer.retrieve_texture_slot(_texture->get_id()));
            }
        }
        else {
            const uint8_t r = static_cast<uint32_t>(_color.x * 255.0f);
            const uint8_t g = static_cast<uint32_t>(_color.y * 255.0f);
            const uint8_t b = static_cast<uint32_t>(_color.z * 255.0f);
            const uint8_t a = static_cast<uint32_t>(_color.w * 255.0f);
            uint_color = a << 24 | b << 16 | g << 8 | r;
        }
        sprite[0] = {
                last_transform * vec3(x, y, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 0.0f),
                texture_slot,
                uint_color
        };
        sprite[1] = {
                last_transform * vec3(x + width, y, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 0.0f),
                texture_slot,
                uint_color
        };
        sprite[2] = {
                last_transform * vec3(x + width, y + height, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 1.0f),
                texture_slot,
                uint_color
        };
        sprite[3] = {
                last_transform * vec3(x, y + height, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 1.0f),
                texture_slot,
                uint_color
        };
        renderer.submit_data(sprite, sizeof(VertexData) * 4);
    }

    void Sprite::set_texture(const Texture *tex)
    {
        _texture = tex;
    }
}
