#include "layer.h"
#include "../renderer/renderer.h"
#include "../../../camera/camera.h"

namespace mrld
{
    Layer::Layer(Shader *shader, Renderer *r, Camera *camera)
    : _shader {shader}
    , _renderer{r}
    , _camera{camera}
    {
        _camera->update();
        _vp_matrix = _camera->get_proj() * _camera->get_view();
        _shader->use();
        _shader->set_mat4("vp_matrix", _vp_matrix);
        _shader->disable();
    }

    Layer::~Layer()
    {
        for (auto &&item : _objects) {
            delete item;
        }
    }

    Layer::Layer(Layer &&o)
    {
        *this = std::move(o);
    }

    Layer &Layer::operator=(Layer &&o)
    {
        _objects = std::move(o._objects);
        o._objects.clear();
        return *this;
    }

    void Layer::add(Renderable *o)
    {
        _objects.push_back(o);
    }

    void Layer::draw()
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
