#pragma once

#define member_floats_count(type, member) (sizeof(((type*)0)->member) / sizeof(float))

#include <vector>
#include <map>

#include "../../shader/shader.h"
#include "../renderable/renderable.h"

namespace mrld
{
    class Drawable;
    class Group;
    struct mat4;
    class Renderer
    {
    public:
        Renderer() = default;
        Renderer(Shader *shader);
        virtual ~Renderer() = default;

        // Should be called before submitting
        virtual void begin() const {};
        // Should be called before flushing
        virtual void end() const {};

        // Can accept aggregates (groups)
        virtual void submit(Renderable &o) { o.submit_self(*this); }
        // Accepts actual models / sprites (with vertex data)
        virtual void submit(Drawable &o) = 0;
        virtual void flush() = 0;

        virtual void push(const mat4 &transform, bool override = false);
        virtual void pop();

        // Assume transform stack is empty when it has only one transform - identity matrix
        inline bool has_transforms_on_stack() const { return _transform_stack.size() > 1; }
        const mat4 &get_last_transform() const { return *_last_transform; }
        inline uint32_t get_n_texture_slots_used() const { return _texture_id_to_texture_slot.size(); }
        int32_t retrieve_texture_slot(uint32_t texture_id);

        void set_shader(Shader *shader) { _shader = shader; }

    protected:
        const uint32_t ATTRIB_INDEX_POSITION = 0;
        const uint32_t ATTRIB_INDEX_NORMAL = 1;
        const uint32_t ATTRIB_INDEX_TEX_COORD = 2;
        const uint32_t ATTRIB_INDEX_TEX_SLOT = 3;
        const uint32_t ATTRIB_INDEX_MATERIAL_SLOT = 4;
        const uint32_t ATTRIB_INDEX_COLOR = 5;
        const uint32_t MAX_TEXTURE_SLOTS = 32;
        const uint32_t VERTEX_SIZE = sizeof(VertexData);

        Shader *_shader;
        std::vector<mat4> _transform_stack;
        const mat4 *_last_transform;
        std::unordered_map<uint32_t, uint32_t> _texture_id_to_texture_slot;
    };
}
