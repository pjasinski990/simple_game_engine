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
        _shader->set_vec3("camera_position", _camera->get_position());
        _shader->set_vec3("camera_direction", _camera->get_direction());
        _shader->disable();
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
        _shader->set_vec3("camera_position", _camera->get_position());
        _shader->set_vec3("camera_direction", _camera->get_direction());

        _renderer->begin();
        for (auto &&item : _objects) {
            _renderer->submit(*item);
        }
        _renderer->end();
        _renderer->flush();
    }

    void Layer::add_point_light(const point_light &l)
    {
        _point_lights.push_back(l);
        _shader->set_point_light(_point_lights.back(), _point_lights.size() - 1);
        _shader->set_int("lights_count", _point_lights.size());
    }
}
