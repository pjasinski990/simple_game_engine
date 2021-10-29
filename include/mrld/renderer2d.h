#pragma once

#include <deque>

#include "renderable.h"
#include "renderer.h"
#include "renderable2d.h"

namespace mrld
{
    class Renderer2D: public Renderer
    {
    public:
        virtual void submit(const Renderable *o) override;
        virtual void flush() override;
    private:
        std::deque<const Renderable*> _render_queue;
    };
}
