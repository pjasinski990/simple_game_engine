#pragma once

namespace mrld
{
    class Renderer2D;
    class Renderable
    {
    public:
        virtual ~Renderable() = default;

        // TODO this should not be a renderer2d // abstract to simply a renderer
        virtual void submit(Renderer2D &renderer) const = 0;
    };
}
