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
        Layer2D(Shader *s, Camera *camera);
        ~Layer2D();
        Layer2D(const Layer2D &o) = delete;
        Layer2D& operator=(const Layer2D &o) = delete;
        Layer2D(Layer2D &&o);
        Layer2D& operator=(Layer2D &&o);

        void draw() override;
        void add(Renderable *o);
    private:
        std::vector<Renderable *> _objects;
    };
}
