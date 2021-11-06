#include "../../../utils/logger.h"
#include "../../../math/mat4.h"
#include "renderer.h"

namespace mrld
{
    void Renderer::push(const mat4 &transform, bool override /* = false */)
    {
        if (override) {
            _transform_stack.push_back(transform);
        }
        else {
            _transform_stack.push_back(_transform_stack.back() * transform);
        }
        _last_transform = &_transform_stack.back();
    }

    void Renderer::pop()
    {
        if (_transform_stack.size() > 1) {
            _transform_stack.pop_back();
            _last_transform = &_transform_stack.back();
        }
        else {
            Logger::log(LogLevel::WRN, "Trying to pop nonexistent transformation from "
                                       "transformation stack");
        }
    }
}
