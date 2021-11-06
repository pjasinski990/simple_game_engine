#pragma once

#include <vector>

namespace mrld
{
    class Renderable;
    struct mat4;
    class Renderer
    {
    public:

        virtual void begin() const {};
        virtual void end() const {};

        virtual void submit(const Renderable &o) = 0;
        virtual void flush() = 0;
        virtual void submit_data(const void *data, uint32_t size) {};

        virtual void push(const mat4 &transform, bool override = false);
        virtual void pop();

        virtual const mat4 &get_last_transform() const { return *_last_transform; }

    protected:
        std::vector<mat4> _transform_stack;
        const mat4 *_last_transform;
    };
}
