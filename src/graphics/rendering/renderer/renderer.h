//
// Created by Piotr on 06/11/2021.
//

namespace mrld
{
    class Renderable;
    struct mat4;
    class Renderer
    {
        virtual void begin() const {};
        virtual void end() const {};

        virtual void submit(const Renderable &o) = 0;
        virtual void flush() = 0;
        virtual void submit_data(const void *data, uint32_t size) {};

        virtual void push(const mat4 &transform, bool override = false) {};
        virtual void pop() {};
    };
}
