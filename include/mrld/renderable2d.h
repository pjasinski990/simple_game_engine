#pragma once

#include "renderable.h"

namespace mrld
{
    class Renderable2D: public Renderable
    {
    public:
        Renderable2D(const Shader *shader, const vec2 &position, const vec2 &size, const vec4 &color, uint32_t z_index = 0);
        virtual ~Renderable2D() override = default;
        virtual void transform() const override;

        void set_z_index(uint32_t z_index) { _z_index = z_index; }
        uint32_t get_z_index() const { return _z_index; }
    private:
        static uint16_t _indices[];
        uint32_t _z_index;
        mat4 _translation;
    };
}
