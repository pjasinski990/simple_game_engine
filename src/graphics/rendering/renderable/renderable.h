#pragma once

#include <vector>
#include "../buffer/vertex_data.h"

namespace mrld
{
    class Renderer;
    class Renderable
    {
    public:
        virtual ~Renderable() = default;
        virtual void submit_self(Renderer &r) = 0;

    protected:
    };
}
