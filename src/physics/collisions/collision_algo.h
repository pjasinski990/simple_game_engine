#pragma once
#include "collision_point.h"
#include "../transform.h"
#include "collider.h"

namespace mrld
{
    class PlaneCollider;
    class SphereCollider;
    namespace coll
    {
        collision_point plane_plane_collision(const transform &ta, const PlaneCollider *a, const transform &tb, const PlaneCollider *b);
        collision_point plane_sphere_collision(const transform &ta, const PlaneCollider *a, const transform &tb, const SphereCollider *b);
        collision_point sphere_plane_collision(const transform &ta, const SphereCollider *a, const transform &tb, const PlaneCollider *b);
        collision_point sphere_sphere_collision(const transform &ta, const SphereCollider *a, const transform &tb, const SphereCollider *b);
    }
}
