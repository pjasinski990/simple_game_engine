#include <glad/glad.h>

#include "mrld/renderer2d.h"

namespace mrld
{
    void Renderer2D::submit(const Renderable *o)
    {
        _render_queue.push_back(o);
    }

    void Renderer2D::flush()
    {
        while (!_render_queue.empty()) {
            const Renderable *sprite = _render_queue.front();
            const VertexArray &vao = sprite->get_vao();
            const IndexBuffer &ibo = sprite->get_ibo();

            sprite->get_shader().use();
            vao.bind();
            ibo.bind();
            sprite->transform();
            glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_SHORT, nullptr);
            ibo.unbind();
            vao.unbind();
            _render_queue.pop_front();
        }
    }
}
