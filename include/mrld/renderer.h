#pragma once

#include "mrld/renderable.h"

namespace mrld
{
    class Renderer
    {
    public:
        virtual void submit(const Renderable *o) = 0;
        virtual void flush() = 0;
    };
}
