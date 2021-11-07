#pragma once

#include "../../../../math/vec2.h"
#include "../../../../math/vec3.h"
#include "../../../../math/vec4.h"
#include "../../../texture/texture.h"
#include "../renderable.h"

namespace mrld
{
    class Renderer2D;
    class Sprite: public Renderable
    {
    public:
        Sprite(const vec3 &position, const vec2 &size = vec2(), const vec4 &color = vec4(), uint32_t z_index = 0, const Texture *tex = nullptr);
        virtual void submit(Renderer &renderer) const override;

        inline vec2 get_size() const { return _size; }
        inline vec4 get_color() const { return _color; }
        inline uint32_t get_z_index() const { return _z_index; }

        void set_texture(const Texture *tex);
        inline void set_position(const vec3 &position) { _position = position; }
        inline void set_size(const vec2 &size) { _size = size; }
        inline void set_color(const vec4 &color) { _color = color; }
    private:
        vec3 _position;
        vec2 _size;
        vec4 _color;
        uint32_t _z_index;
        const Texture *_texture;
    };
}
