#pragma once

#include <vector>

#include "../../../math/mat4.h"
#include "../renderer/renderable.h"

namespace mrld
{
    class Renderer2D;
    class Group2D: public Renderable
    {
    public:
        Group2D(const mat4 &transformation);
        ~Group2D();
        // TODO adding by pointer, allocation on heap, find a better way?
        void add(const Renderable *o);
        void submit(Renderer2D &renderer) const override;

    private:
        mat4 _transformation;
        std::vector<const Renderable*> _children;
    };
}
