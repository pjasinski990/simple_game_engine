#pragma once

#include "body.h"
#include "physics_properties.h"
#include "transform.h"

namespace mrld
{
    class Model;
    class Collider;
    class RigidBody: public Body
    {
    public:
        RigidBody(Model *model, Collider *collider, const physics_properties &properties);

    private:

    };
}
