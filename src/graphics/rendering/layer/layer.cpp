#include "layer.h"

namespace mrld
{
    Layer::Layer(Shader *shader, Renderer *r, const mat4 &projection)
    : _shader {shader}
    , _renderer{r}
    , _projection{projection}
    {
        _shader->use();
        _shader->set_mat4("proj_matrix", _projection);
        _shader->disable();
    }
}
