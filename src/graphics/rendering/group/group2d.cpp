#include "group2d.h"
#include "../renderer/renderer2d/renderer2d.h"
#include "../renderer/renderable.h"

namespace mrld
{

    Group2D::Group2D(const mat4 &transformation)
    : _transformation{std::move(transformation)}
    { }

    Group2D::~Group2D()
    {
        for (const Renderable *o : _children) {
            delete o;
        }
    }

    void Group2D::add(const Renderable *o)
    {
        _children.push_back(o);
    }

    void Group2D::submit(Renderer &renderer) const
    {
        renderer.push(_transformation);
        renderer.begin();
        for (const Renderable *r : _children) {
            r->submit(renderer);
        }
        renderer.end();
        renderer.pop();
    }
}
