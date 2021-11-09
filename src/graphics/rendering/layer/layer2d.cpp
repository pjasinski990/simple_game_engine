#include "layer2d.h"
#include "../renderer/renderer2d/renderer2d.h"

namespace mrld
{
    Layer2D::Layer2D(Shader *s, const mat4 &projection)
    : Layer(s, new Renderer2D(s), projection)
    { }

    void Layer2D::add(Renderable *o)
    {
        _objects.push_back(o);
    }

    Layer2D::~Layer2D()
    {
        for (auto &&item : _objects) {
            delete item;
        }
        delete _renderer;
    }

    void Layer2D::draw()
    {
        _shader->use();
        _renderer->begin();
        for (auto &&item : _objects) {
            _renderer->submit(*item);
        }
        _renderer->end();
        _renderer->flush();

    }

    Layer2D::Layer2D(Layer2D &&o)
    : Layer(std::move(o))
    {
        *this = std::move(o);
    }

    Layer2D &Layer2D::operator=(Layer2D &&o)
    {
        _objects = std::move(o._objects);
        o._objects.clear();
        return *this;
    }
}
