#pragma once

#include "../renderable.h"

namespace mrld
{
    class Texture;
    class Drawable: public Renderable
    {
    public:
        Drawable(const Texture *tex = nullptr): _texture{tex} {}
        virtual VertexData* get_vertices() = 0;
        virtual uint32_t get_vertices_count() const = 0;
        virtual const uint32_t* get_indices() const = 0;
        virtual uint32_t get_indices_count() const = 0;
        virtual void submit(Renderer &r) override = 0;

        virtual const Texture* get_texture() const { return _texture; }

    protected:
        std::vector<uint32_t> _indices;
        std::vector<VertexData> _vertices;
        const Texture *_texture;

    };
}