#include "group.h"
#include "../../renderer/renderer2d.h"

namespace mrld
{

    Group::Group(const mat4 &transformation)
    : _transformation{std::move(transformation)}
    { }

    Group::~Group()
    {
        for (auto && item : _children) {
            delete item;
        }
    }

    Group::Group(Group &&o)
    {
        *this = std::move(o);
    }

    Group &Group::operator=(Group &&o)
    {
        _transformation = std::move(o._transformation);
        _children = std::move(o._children);
        o._children.clear();
        return *this;
    }

    void Group::submit(Renderer &r)
    {
        r.push(_transformation);
        r.begin();
        for (auto &&item : _children) {
            item->submit(r);
        }
        r.end();
        r.pop();
    }

    void Group::add(Renderable *o)
    {
        _children.push_back(o);
    }
}
