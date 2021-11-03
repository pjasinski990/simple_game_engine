#pragma once

#include "../../shader/shader.h"
#include "../renderer/renderer2d/renderable2d.h"
#include "../renderer/renderer2d/renderer2d.h"

namespace mrld
{
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void draw() = 0;
    protected:
        Layer(const Shader &shader, mat4 projection);

        Shader _shader;
        Renderer2D _renderer;
        mat4 _projection;
    };
}
