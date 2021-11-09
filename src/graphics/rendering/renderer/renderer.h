#pragma once

#include <vector>
#include <map>

#include "../../shader/shader.h"

namespace mrld
{
    class Renderable;
    struct mat4;
    class Renderer
    {
    public:
        Renderer(const Shader *shader);
        virtual ~Renderer() = default;

        virtual void begin() const {};
        virtual void end() const {};

        virtual void submit(const Renderable &o) = 0;
        virtual void flush() = 0;
        virtual void submit_data(const void *data, uint32_t size) {};

        virtual void push(const mat4 &transform, bool override = false);
        virtual void pop();

        const mat4 &get_last_transform() const { return *_last_transform; }
        inline uint32_t get_n_texture_slots_used() const { return _texture_id_to_texture_slot.size(); }
        int32_t retrieve_texture_slot(uint32_t texture_id);

        void set_shader(const Shader *shader) { _shader = shader; }

    protected:
        constexpr static uint32_t ATTRIB_INDEX_POSITION = 0;
        constexpr static uint32_t ATTRIB_INDEX_NORMAL = 1;
        constexpr static uint32_t ATTRIB_INDEX_TEX_COORD = 2;
        constexpr static uint32_t ATTRIB_INDEX_TEX_SLOT = 3;
        constexpr static uint32_t ATTRIB_INDEX_COLOR = 4;

        constexpr static uint32_t MAX_TEXTURE_SLOTS = 32;

        const Shader *_shader;

        std::vector<mat4> _transform_stack;
        const mat4 *_last_transform;

        std::unordered_map<uint32_t, uint32_t> _texture_id_to_texture_slot;
    };
}
