#pragma once

#include "../renderable.h"
#include "../../renderer/renderer.h"
#include "../../../materials/material.h"

namespace mrld
{
    class Texture;
    class Drawable: public Renderable
    {
    public:
        Drawable(const Texture *tex = nullptr): _texture{tex} {}
        virtual VertexData* get_vertices() = 0;
        virtual uint32_t get_vertices_count() const = 0;
        virtual const uint16_t* get_indices() const = 0;
        virtual uint32_t get_indices_count() const = 0;
        virtual void assign_material(const material &m);
        virtual void submit_self(Renderer &r) override { r.submit(*this); }

        const Texture* get_texture() const { return _texture; }
        void set_texture(Texture *tex) { _texture = tex; }
        const std::vector<material>& get_materials() const { return _materials; }
        void set_materials(const std::vector<material> &materials) { _materials = materials; }

    protected:
        std::vector<uint16_t> _indices;
        std::vector<VertexData> _vertices;
        std::vector<material> _materials;
        const Texture *_texture;

    };
}
