#pragma once

#include <vector>

#include "../../../math/mat4.h"
#include "../../lighting/light.h"

namespace mrld
{
    class Shader;
    class Renderer;
    class Renderable;
    class Camera;
    class Layer
    {
    public:
        virtual ~Layer();
        Layer(Shader *s, Renderer *r, Camera *camera);
        Layer(const Layer &o) = delete;
        Layer& operator=(const Layer &o) = delete;
        Layer(Layer &&o);
        Layer& operator=(Layer &&o);

        virtual void draw();
        virtual void add(Renderable *o);
        virtual void add_light(const light &l);

    protected:
        Shader *_shader;
        Renderer *_renderer;
        Camera *_camera;
        mat4 _vp_matrix;

        std::vector<Renderable*> _objects;
        std::vector<light> _lights;
    };
}
