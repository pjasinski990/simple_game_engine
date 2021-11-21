#include "layer2d.h"
#include "../renderer/renderer2d.h"
#include "../../camera/camera.h"

namespace mrld
{
    Layer2D::Layer2D(Shader *s, Camera *camera)
    : Layer(s, new Renderer2D(s), camera)
    { }

    Layer2D::~Layer2D()
    {
        for (auto &&item : _objects) {
            delete item;
        }
        delete _renderer;
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

    void Layer2D::add(Renderable *o)
    {
        _objects.push_back(o);
    }

    void Layer2D::draw()
    {
        _camera->update();
        _vp_matrix = _camera->get_proj() * _camera->get_view();

        _shader->use();
        _shader->set_mat4("vp_matrix", _vp_matrix);
        _renderer->begin();
        for (auto &&item : _objects) {
            _renderer->submit(*item);
        }
        _renderer->end();
        _renderer->flush();
    }
}
