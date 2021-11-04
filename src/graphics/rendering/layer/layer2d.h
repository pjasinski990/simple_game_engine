#pragma once

#include <vector>
#include <memory>

#include "layer.h"

namespace mrld
{
    class Renderable;
    class Layer2D: public Layer
    {
    public:
        Layer2D(const Shader &s, mat4 projection);
        ~Layer2D();
        void draw() override;
        // TODO better way to add renderable objs
        void add(Renderable *o);
    private:
        std::vector<Renderable *> _objects;
    };
}
