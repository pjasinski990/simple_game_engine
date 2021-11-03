#pragma once

namespace mrld
{
    class Renderable;
    class Renderer
    {
    public:
        virtual void submit(const Renderable &o) = 0;
        virtual ~Renderer() = default;
    };
}
