#pragma once

#include "../../../../math/vec2.h"
#include "../../../../math/vec3.h"
#include "../../../../math/vec4.h"
#include "../../../texture/texture.h"
#include "../../../color.h"
#include "../../renderer/renderer.h"
#include "drawable.h"

namespace mrld
{
    class Renderer2D;
    class Sprite: public Drawable
    {
    public:
        Sprite(const vec3 &position, const vec2 &size, const Texture *tex = nullptr, const vec4 &color = color::BLACK);
        VertexData* get_vertices() override;
        inline uint32_t get_vertices_count() const override { return 4u; };
        const uint16_t* get_indices() const override;
        uint32_t get_indices_count() const override { return 6u; }

        inline vec2 get_size() const { return _size; }
        inline vec4 get_color() const { return _color; }

        void set_texture(const Texture *tex);
        inline void set_position(const vec3 &position) { _position = position; }
        inline void set_size(const vec2 &size) { _size = size; }
        inline void set_color(const vec4 &color) { _color = color; }
    private:
        vec3 _position;
        vec2 _size;
        vec4 _color;
    };
}
