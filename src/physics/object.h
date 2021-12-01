#pragma once

#include "physics_properties.h"
#include "transform.h"

namespace mrld
{
    class Model;
    class Collider;
    class Object
    {
    public:
        // TODO rename Object to Body, inherit from it in RigidBody which has dynamic properties instead of only being collidible
        Object(Model *model, Collider *collider, const physics_properties &properties);

        inline Model *get_model() { return _model; }
        inline const Model *get_model() const { return _model; }
        inline const Collider *get_collider() const { return _collider; }
        void update();

        physics_properties phys_properties;
        transform t;
        bool has_physics;
        bool is_fixed;

    private:
        Model *_model;
        Collider *_collider;
    };
}
