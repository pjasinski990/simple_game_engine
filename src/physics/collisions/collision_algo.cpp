#include <cmath>

#include "collision_algo.h"
#include "colliders/plane_collider.h"
#include "colliders/sphere_collider.h"

namespace mrld
{
    namespace coll
    {
        collision_point plane_plane_collision(const transform &ta, const PlaneCollider *a, const transform &tb, const PlaneCollider *b)
        {
            collision_point res;
            res.has_collision = false;
            return res;
        }

        collision_point plane_sphere_collision(const transform &ta, const PlaneCollider *a, const transform &tb, const SphereCollider *b)
        {
            collision_point res;
            vec3 sphere_center_actual_pos = tb.position + b->get_center();
            vec3 sphere_center_relative_pos = sphere_center_actual_pos - ta.position - a->get_normal() * a->get_distance();
            float dist = (sphere_center_relative_pos).dot(a->get_normal());
            res.has_collision = fabs(dist) < b->get_radius();
            if (res.has_collision) {
                res.a = sphere_center_actual_pos - a->get_normal() * dist;
                res.b = sphere_center_actual_pos - a->get_normal() * b->get_radius();
                vec3 diff = res.b - res.a;
                res.collision_depth = diff.magnitude();
                res.normal = diff.normalized();
            }
            return res;
        }

        collision_point sphere_plane_collision(const transform &ta, const SphereCollider *a, const transform &tb, const PlaneCollider *b)
        {
            return plane_sphere_collision(tb, b, ta, a);
        }

        collision_point sphere_sphere_collision(const transform &ta, const SphereCollider *a, const transform &tb, const SphereCollider *b)
        {
            collision_point res;
            vec3 sphere_center_actual_pos_a = ta.position + a->get_center();
            vec3 sphere_center_actual_pos_b = tb.position + b->get_center();
            float dist = (sphere_center_actual_pos_a - sphere_center_actual_pos_b).magnitude();
            res.has_collision = fabs(dist) < a->get_radius() + b->get_radius();
            if (res.has_collision) {
                res.normal = (sphere_center_actual_pos_a - sphere_center_actual_pos_b).normalized();
                res.a = sphere_center_actual_pos_a - res.normal * a->get_radius();
                res.b = sphere_center_actual_pos_b + res.normal * b->get_radius();
                res.collision_depth = a->get_radius() + b->get_radius() - dist;
            }
            return res;
        }
    }
}
