#include "../../../utils/logger.h"
#include "../../../math/mat4.h"
#include "renderer.h"

namespace mrld
{
    Renderer::Renderer(Shader *shader)
    : _shader{shader}
    { }

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
            Logger::log(LogLevel::WRN, "Trying to pop non-existent transformation from "
                                       "transformation stack");
        }
    }

    int32_t Renderer::retrieve_texture_slot(uint32_t texture_id)
    {
        if (_texture_id_to_texture_slot.contains(texture_id)) {
            return _texture_id_to_texture_slot[texture_id];
        }
        else if (get_n_texture_slots_used() >= MAX_TEXTURE_SLOTS) {
            return -1;
        }

        if (!_shader) {
            Logger::log(LogLevel::ERR, "Trying to set sampler uniform value but shader is null.");
            throw std::runtime_error("Error retrieving texture slot.");
        }
        else {
            _texture_id_to_texture_slot[texture_id] = get_n_texture_slots_used();
            return _texture_id_to_texture_slot[texture_id];
        }
    }
}
