#include "layer.h"

namespace mrld
{
    // TODO projection set by layer? figure this out
    Layer::Layer(Shader *shader, Renderer *r, const mat4 &projection)
    : _shader {shader}
    , _renderer{r}
    , _projection{projection}
    {
//        _shader->use();
//        _shader->set_mat4("projection_matrix", _projection);
//        _shader->disable();
    }
}
