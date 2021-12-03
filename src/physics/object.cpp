#include "object.h"
#include "../graphics/rendering/renderable/drawable/model.h"

namespace mrld
{
    Object::Object(Model *model, Collider *collider, const physics_properties &properties)
    : _model{model}
    , _collider{collider}
    , phys_properties{properties}
    , t{vec3(), vec3(1.0f, 1.0f, 1.0f), quat()}
    , has_physics{true}
    , is_fixed{true}
    {
        /* no-op */
    }

    void Object::update_model()
    {
        _model->set_model_matrix(
                mat4::translate(t.position)
                * mat4::rotate(t.rotation)
                * mat4::scale(t.scale)
                );
    }
}
