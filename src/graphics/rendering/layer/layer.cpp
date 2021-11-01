#include "layer.h"

namespace mrld
{
    Layer::Layer(const Shader &shader, mat4 projection)
    : _shader {shader}
    // TODO renderer2D shouldn't be here
    , _renderer {Renderer2D()}
    , _projection {mat4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)}
    {
        _shader.use();
        _shader.set_mat4("proj_matrix", projection);
        _shader.remove();
    }
}
