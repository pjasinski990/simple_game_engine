#pragma once

namespace mrld
{
    class Renderer;
    class Renderable
    {
    public:
        virtual ~Renderable() = default;
        virtual void submit(Renderer &renderer) const = 0;
    };
}
