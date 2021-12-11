#pragma once

#include "physics_properties.h"
#include "transform.h"

namespace mrld
{
    class Model;
    class Collider;
    class Body
    {
    public:
        Body(Model *model, Collider *collider, const physics_properties &properties);

        bool is_dynamic() const { return _is_dynamic; }
        inline Model *get_model() { return _model; }
        inline const Collider *get_collider() const { return _collider; }
        void update_model();

        physics_properties phys_properties;
        transform t;

    protected:
        bool _is_dynamic;
        bool _is_trigger;

        Model *_model;
        Collider *_collider;
    };
}