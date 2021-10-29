#include "mrld/renderable2d.h"

namespace mrld
{
    uint16_t Renderable2D::_indices[] = {
        0, 1, 2,
        0, 3, 1
    };

Renderable2D::Renderable2D(const Shader *shader, const vec2 &position, const vec2 &size, const vec4 &color, uint32_t z_index)
        : Renderable(shader)
    {
        _translation = mat4::translate(mrld::vec3(position.x, position.y, 0.0f));
        float z = static_cast<float>(z_index);
        float vertices[] {
            0, 0, z,
            size.x, size.y, z,
            0, size.y, z,
            size.x, 0, z,
        };
        float colors[] {
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w
        };

        _ibo = IndexBuffer(Renderable2D::_indices, 6);
        _vao.add_buffer(new AttribDataBuffer(vertices, 3 * 4, 3), 0);
        _vao.add_buffer(new AttribDataBuffer(colors, 4 * 4, 4), 1);
    }

    void Renderable2D::transform() const
    {
        get_shader().set_mat4("model_matrix", _translation);
    }
}
