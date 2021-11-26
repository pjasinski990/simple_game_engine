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
        Object(Model *model, Collider *collider, const physics_properties &properties);

        inline Model *get_model() { return _model; }
        inline const Model *get_model() const { return _model; }
        inline Collider *get_collider() { return _collider; }
        inline const Collider *get_collider() const { return _collider; }
        inline transform& get_transform() { return _transform; }
        inline const transform& get_transform() const { return _transform; }
        inline physics_properties& get_properties() { return _phys_properties; }
        inline const physics_properties& get_properties() const { return _phys_properties; }
        void update();

    private:
        Model *_model;
        Collider *_collider;
        physics_properties _phys_properties;
        transform _transform;

        bool _has_physics;
        bool _is_fixed;
    };
}
