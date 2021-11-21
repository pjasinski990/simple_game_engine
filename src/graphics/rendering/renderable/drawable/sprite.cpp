#include "../../../../math/vec3.h"
#include "../../../../math/vec2.h"
#include "../../../../utils/logger.h"
#include "sprite.h"
#include "../../renderer/renderer2d.h"

namespace mrld
{
    Sprite::Sprite(const vec3 &position, const vec2 &size, const Texture *tex /* = nullptr */, const vec4 &color /* = color::BLACK */)
    : Drawable(tex)
    , _position{position}
    , _size {size}
    , _color(color)
    {
        _indices = {0, 1, 2, 2, 3, 0};

        const float x = _position.x;
        const float y = _position.y;
        const float z = _position.z;
        const float width = _size.x;
        const float height = _size.y;
        const float texture_slot = -1.0f;

        uint32_t uint_color = 0;
        if (!_texture) {
            const uint8_t r = static_cast<uint32_t>(_color.x * 255.0f);
            const uint8_t g = static_cast<uint32_t>(_color.y * 255.0f);
            const uint8_t b = static_cast<uint32_t>(_color.z * 255.0f);
            const uint8_t a = static_cast<uint32_t>(_color.w * 255.0f);
            uint_color = a << 24 | b << 16 | g << 8 | r;
        }
        _vertices.emplace_back(
            VertexData {
                vec3(x, y, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 0.0f),
                texture_slot,
                uint_color
            }
        );
        _vertices.emplace_back(
            VertexData {
                vec3(x + width, y, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 0.0f),
                texture_slot,
                uint_color
            }
        );
        _vertices.emplace_back(
            VertexData {
                vec3(x + width, y + height, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(1.0f, 1.0f),
                texture_slot,
                uint_color
            }
        );
        _vertices.emplace_back(
            VertexData {
                vec3(x, y + height, z),
                vec3(0.0f, 0.0f, 1.0f),
                vec2(0.0f, 1.0f),
                texture_slot,
                uint_color
            }
        );
    }

    VertexData* Sprite::get_vertices()
    {
        return _vertices.data();
    }

    const uint32_t* Sprite::get_indices() const
    {
        return _indices.data();
    }

    void Sprite::set_texture(const Texture *tex)
    {
        _texture = tex;
    }
}
