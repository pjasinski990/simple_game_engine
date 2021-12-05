#pragma once

#include "collision_point.h"
#include "../transform.h"

namespace mrld
{
    class PlaneCollider;
    class SphereCollider;
    class Collider
    {
    public:
        virtual ~Collider() = default;
        virtual collision_point check_collision(const transform &ta, const Collider *o, const transform &tb) const = 0;
        virtual collision_point check_collision(const transform &ta, const PlaneCollider *o, const transform &tb) const = 0;
        virtual collision_point check_collision(const transform &ta, const SphereCollider *o, const transform &tb) const = 0;
    protected:

    };
}
