#include "layer2d.h"
#include "../../../../math/constants.h"

namespace mrld
{
    Layer2D::Layer2D(const Shader &s, mat4 projection)
    : Layer(s, projection)
    { }

    void Layer2D::add(Renderable2D *o)
    {
        _objects.push_back(o);
    }

    Layer2D::~Layer2D()
    {
        for (auto &&item : _objects) {
            delete item;
        }
    }

    void Layer2D::draw()
    {
        _shader.use();
        _renderer.begin();
        _renderer.push(mat4::rotate_z(math::constants::pi / 3.0f));
//        _renderer.push(mat4::translate(vec3(1.0f, 1.0f)));
        for (auto &&item : _objects) {
            _renderer.submit(*item);
        }
        _renderer.pop();
        _renderer.end();
        _renderer.flush();
    }
}
