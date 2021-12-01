#pragma once

#include "../collider.h"
#include "../collision_algo.h"

namespace mrld
{
    class PlaneCollider;
    class SphereCollider: public Collider
    {
    public:
        SphereCollider(const vec3 &center, float r): _center{center}, _r{r} {}

        inline collision_point check_collision(const transform &ta, const Collider *o, const transform &tb) const override
        {
            return o->check_collision(tb, this, ta);
        }
        inline collision_point check_collision(const transform &ta, const PlaneCollider *o, const transform &tb) const override
        {
            return coll::sphere_plane_collision(ta, this, tb, o);
        }
        inline collision_point check_collision(const transform &ta, const SphereCollider *o, const transform &tb) const override
        {
            return coll::sphere_sphere_collision(ta, this, tb, o);
        }

        inline const vec3& get_center() const { return _center; }
        inline const float get_radius() const {return _r; }
    private:
        vec3 _center;
        float _r;
    };
}
