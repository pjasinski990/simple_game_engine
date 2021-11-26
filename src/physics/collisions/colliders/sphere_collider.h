#pragma once

#include "../collider.h"
#include "../collision_algo.h"

namespace mrld
{
    class PlaneCollider;
    class SphereCollider: public Collider
    {
    public:
        SphereCollider(float r): _r{r} {}

        inline collision_point check_collision(const transform &ta, const Collider *o, const transform &tb) const override
        {
            return o->check_collision(tb, this, ta);
        }
        inline collision_point check_collision(const transform &ta, const PlaneCollider *o, const transform &tb) const
        {
            return coll::sphere_plane_collision(ta, this, tb, o);
        }
        inline collision_point check_collision(const transform &ta, const SphereCollider *o, const transform &tb) const
        {
            return coll::sphere_sphere_collision(ta, this, tb, o);
        }

    private:
        float _r;
    };
}
