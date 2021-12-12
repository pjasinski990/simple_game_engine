#pragma once

#include <vector>

#include "../../../math/mat4.h"
#include "../../lighting/directional_light.h"
#include "../../lighting/point_light.h"

namespace mrld
{
    class Shader;
    class Renderer;
    class Renderable;
    class Camera;
    class Layer
    {
    public:
        Layer() = default;
        Layer(Shader *s, Renderer *r, Camera *camera);
        virtual ~Layer() = default;

        virtual void draw();
        virtual void add(Renderable *o);
        virtual void add_point_light(const point_light &l);

    protected:
        Shader *_shader;
        Renderer *_renderer;
        Camera *_camera;
        mat4 _vp_matrix;

        std::vector<Renderable*> _objects;
        std::vector<point_light> _point_lights;
    };
}
