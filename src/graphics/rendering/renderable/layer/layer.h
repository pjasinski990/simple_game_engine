#pragma once

#include "../../../../math/mat4.h"

namespace mrld
{
    class Shader;
    class Renderer;
    class Camera;
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void draw() = 0;
    protected:
        Layer(Shader *shader, Renderer *renderer, Camera *camera);

        Shader *_shader;
        Renderer *_renderer;
        Camera *_camera;
        mat4 _vp_matrix;
    };
}
