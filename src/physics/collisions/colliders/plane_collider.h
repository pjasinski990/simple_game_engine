#pragma once

#include "../collider.h"
#include "../collision_algo.h"

namespace mrld
{
    class SphereCollider;
    class PlaneCollider: public Collider
    {
    public:
        PlaneCollider(const vec3 &normal, float distance): _normal{normal.normalized()}, _distance{distance} {}

        inline collision_point check_collision(const transform &ta, const Collider *o, const transform &tb) const override
        {
            return o->check_collision(tb, this, ta);
        }
        inline collision_point check_collision(const transform &ta, const PlaneCollider *o, const transform &tb) const override
        {
            return coll::plane_plane_collision(ta, this, tb, o);
        }
        inline collision_point check_collision(const transform &ta, const SphereCollider *o, const transform &tb) const override
        {
            return coll::plane_sphere_collision(ta, this, tb, o);
        }

        inline const vec3& get_normal() const { return _normal; }
        inline const float get_distance() const {return _distance; }
    private:
        vec3 _normal;
        float _distance;
    };
}
