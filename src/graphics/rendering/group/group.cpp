#include "group.h"
#include "../renderer/renderer2d/renderer2d.h"

namespace mrld
{

    Group::Group(const mat4 &transformation)
    : _transformation{std::move(transformation)}
    { }

    Group::~Group()
    {
        for (const Renderable *o : _children) {
            delete o;
        }
    }

    void Group::add(const Renderable *o)
    {
        _children.push_back(o);
    }

    void Group::submit(Renderer &renderer) const
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
