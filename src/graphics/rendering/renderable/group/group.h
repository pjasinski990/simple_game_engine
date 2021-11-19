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

        void add(const Renderable *o);
        void submit(Renderer &renderer) const override;

    private:
        mat4 _transformation;
        std::vector<const Renderable*> _children;
    };
}
