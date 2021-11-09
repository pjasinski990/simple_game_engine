#pragma once

#include "../../shader/shader.h"
#include "../renderer/renderer.h"

namespace mrld
{
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void draw() = 0;
    protected:
        Layer(Shader *shader, Renderer *renderer, const mat4 &projection);

        Shader *_shader;
        Renderer *_renderer;
        mat4 _projection;
    };
}
