#pragma once

#include "../collider.h"
#include "../collision_algo.h"

namespace mrld
{
    class SphereCollider;
    class RayCollider: public Collider
    {
    public:
        RayCollider(const vec3 &source, const vec3 &direction): _source{source}, _direction{direction.normalized()} {}

        inline collision_point check_collision(const transform &ta, const Collider *o, const transform &tb) const override
        {
            return o->check_collision(tb, this, ta);
        }
        inline collision_point check_collision(const transform &ta, const PlaneCollider *o, const transform &tb) const override
        {
            return coll::ray_plane_collision(ta, this, tb, o);
        }
        inline collision_point check_collision(const transform &ta, const SphereCollider *o, const transform &tb) const override
        {
            return coll::ray_sphere_collision(ta, this, tb, o);
        }
        inline collision_point check_collision(const transform &ta, const RayCollider *o, const transform &tb) const override
        {
            return coll::ray_ray_collision(ta, this, tb, o);
        }

        inline const vec3& get_source() const { return _source; }
        inline const vec3& get_direction() const {return _direction; }
    private:
        vec3 _source;
        vec3 _direction;
    };
}
