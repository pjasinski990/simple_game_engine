#pragma once

#include <vector>

#include "../../../../math/mat4.h"
#include "../renderable.h"

namespace mrld
{
    class Renderer;
    class Group: public Renderable
    {
    public:
        Group(const mat4 &transformation);
        ~Group();
        Group(const Group &o) = delete;
        Group& operator=(const Group &o) = delete;
        Group(Group &&o);
        Group& operator=(Group &&o);

        void submit(Renderer &r) override;
        void add(Renderable *o);
        const std::vector<Renderable*>& get_children() const { return _children; }
        const mat4& get_transformation() const { return _transformation; }

    private:
        mat4 _transformation;
        std::vector<Renderable*> _children;
    };
}
