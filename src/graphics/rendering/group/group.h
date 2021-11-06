#pragma once

#include <vector>

#include "../../../math/mat4.h"
#include "../renderer/renderable.h"

namespace mrld
{
    class Renderer;
    class Group: public Renderable
    {
    public:
        Group(const mat4 &transformation);
        ~Group();
        // TODO adding by pointer, allocation on heap, find a better way?
        void add(const Renderable *o);
        void submit(Renderer &renderer) const override;

    private:
        mat4 _transformation;
        std::vector<const Renderable*> _children;
    };
}
