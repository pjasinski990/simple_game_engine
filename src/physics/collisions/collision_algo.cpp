#include "collision_algo.h"
#include "colliders/plane_collider.h"

namespace mrld
{
    namespace coll
    {
        collision_point plane_plane_collision(const transform &ta, const PlaneCollider *a, const transform &tb, const Collider *b)
        {
            collision_point res;
            res.has_collision = false;

            return res;
        }

        collision_point plane_sphere_collision(const transform &ta, const PlaneCollider *a, const transform &tb, const SphereCollider *b)
        {
            collision_point res;
            res.has_collision = false;

            return res;
        }

        collision_point sphere_plane_collision(const transform &ta, const SphereCollider *a, const transform &tb, const PlaneCollider *b)
        {
            collision_point res;
            res.has_collision = false;

            return res;
        }

        collision_point sphere_sphere_collision(const transform &ta, const SphereCollider *a, const transform &tb, const SphereCollider *b)
        {
            collision_point res;
            res.has_collision = false;

            return res;
        }

    }
}
