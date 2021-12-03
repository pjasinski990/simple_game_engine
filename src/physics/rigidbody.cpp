#include "rigidbody.h"
#include "../graphics/rendering/renderable/drawable/model.h"

namespace mrld
{
    RigidBody::RigidBody(Model *model, Collider *collider, const physics_properties &properties)
    : Body(model, collider, properties)
    {
        _is_dynamic = true;
    }

}
