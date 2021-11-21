#include "layer.h"
#include "../../../shader/shader.h"
#include "../../../camera/camera.h"

namespace mrld
{
    Layer::Layer(Shader *shader, Renderer *r, Camera *camera)
    : _shader {shader}
    , _renderer{r}
    , _camera{camera}
    {
        _camera->update();
        _vp_matrix = _camera->get_proj() * _camera->get_view();
        _shader->use();
        _shader->set_mat4("vp_matrix", _vp_matrix);
        _shader->disable();
    }
}
