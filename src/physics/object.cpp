#include "object.h"
#include "../graphics/rendering/renderable/drawable/model.h"

namespace mrld
{
    Object::Object(Model *model, Collider *collider, const physics_properties &properties)
    : _model{model}
    , _collider{collider}
    , _phys_properties{properties}
    , _transform{vec3(), vec3(1.0f, 1.0f, 1.0f), quat()}
    , _has_physics{true}
    , _is_fixed{false}
    {
        /* no-op */
    }

    void Object::update()
    {
        _transform.position = _phys_properties.position;
        _model->set_model_matrix(
                mat4::translate(_transform.position)
                * mat4::rotate(_transform.rotation)
                * mat4::scale(_transform.scale)
                );
    }
}
