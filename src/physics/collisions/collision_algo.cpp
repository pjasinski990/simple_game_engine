#include <cmath>

#include "collision_algo.h"
#include "colliders/plane_collider.h"
#include "colliders/sphere_collider.h"
#include "colliders/ray_collider.h"

namespace mrld
{
    namespace coll
    {
        collision_point plane_plane_collision(const transform &ta, const PlaneCollider *a, const transform &tb, const PlaneCollider *b)
        {
            return collision_point();
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

        collision_point plane_ray_collision(const transform &ta, const PlaneCollider* a, const transform &tb, const RayCollider *b)
        {
            collision_point res;
            vec3 ray_relative_source = b->get_source() + tb.position - ta.position - a->get_normal() * a->get_distance();
            res.has_collision = b->get_direction().dot(a->get_normal()) < 0.0f;
            if (res.has_collision) {
                float d = -ray_relative_source.dot(a->get_normal()) / b->get_direction().dot(a->get_normal());
                res.a = ray_relative_source + d * b->get_direction() + ta.position;
                res.b = b->get_source() + tb.position;
                res.normal = (res.b - res.a).normalized();
                res.collision_depth = -1.0f * d;
            }
            return res;
        }

        collision_point sphere_plane_collision(const transform &ta, const SphereCollider *a, const transform &tb, const PlaneCollider *b)
        {
            collision_point res;
            vec3 sphere_center_actual_pos = ta.position + a->get_center();
            vec3 sphere_center_relative_pos = sphere_center_actual_pos - tb.position - b->get_normal() * b->get_distance();
            float dist = (sphere_center_relative_pos).dot(b->get_normal());
            res.has_collision = fabs(dist) < a->get_radius();
            if (res.has_collision) {
                res.a = sphere_center_actual_pos - b->get_normal() * a->get_radius();
                res.b = sphere_center_actual_pos - b->get_normal() * dist;
                vec3 diff = res.b - res.a;
                res.collision_depth = diff.magnitude();
                res.normal = diff.normalized();
            }
            return res;
        }

        collision_point sphere_sphere_collision(const transform &ta, const SphereCollider *a, const transform &tb, const SphereCollider *b)
        {
            collision_point res;
            vec3 sphere_center_actual_pos_a = ta.position + a->get_center();
            vec3 sphere_center_actual_pos_b = tb.position + b->get_center();
            float dist = (sphere_center_actual_pos_a - sphere_center_actual_pos_b).magnitude();
            float depth = -1.0f * (dist - a->get_radius() - b->get_radius());
            res.has_collision = depth > 0.0f;
            if (res.has_collision) {
                res.normal = (sphere_center_actual_pos_a - sphere_center_actual_pos_b).normalized();
                res.a = sphere_center_actual_pos_a - res.normal * a->get_radius();
                res.b = sphere_center_actual_pos_b + res.normal * b->get_radius();
                res.collision_depth = depth;
            }
            return res;
        }

        collision_point sphere_ray_collision(const transform &ta, const SphereCollider* a, const transform &tb, const RayCollider *b)
        {
            collision_point res;
            vec3 ray_source_actual_position = b->get_source() + tb.position;
            vec3 sphere_center_actual_position = a->get_center() + ta.position;
            vec3 diff = sphere_center_actual_position - ray_source_actual_position;
            res.has_collision = false;

            float on_ray_proj = diff.dot(b->get_direction());
            // ray cast in other direction
            if (on_ray_proj < 0.0f) {
                res.has_collision = false;
                return res;
            }

            float l2 = diff.magnitude_squared();
            float d2 = l2 - on_ray_proj * on_ray_proj;
            float r2 = a->get_radius() * a->get_radius();
            res.has_collision = d2 < r2;
            if (res.has_collision) {
                float on_ray_proj_pen2 = r2 - d2;
                res.collision_depth = -1.0f * (on_ray_proj - sqrtf(on_ray_proj_pen2));
                res.a = ray_source_actual_position - b->get_direction() * res.collision_depth;
                res.b = b->get_source() + tb.position;
                res.normal = (res.b - res.a).normalized();
            }
            return res;
        }

        collision_point ray_plane_collision(const transform &ta, const RayCollider* a, const transform &tb, const PlaneCollider *b)
        {
            collision_point res;
            vec3 ray_relative_source = a->get_source() + ta.position - tb.position - b->get_normal() * b->get_distance();
            res.has_collision = a->get_direction().dot(b->get_normal()) < 0.0f;
            if (res.has_collision) {
                float d = -ray_relative_source.dot(b->get_normal()) / a->get_direction().dot(b->get_normal());
                res.a = a->get_source() + ta.position;
                res.b = ray_relative_source + d * a->get_direction() + tb.position;
                res.normal = (res.b - res.a).normalized();
                res.collision_depth = -1.0f * d;
            }
            return res;
        }

        collision_point ray_sphere_collision(const transform &ta, const RayCollider* a, const transform &tb, const SphereCollider *b)
        {
            collision_point res;
            vec3 ray_source_actual_position = a->get_source() + ta.position;
            vec3 sphere_center_actual_position = b->get_center() + tb.position;
            vec3 diff = sphere_center_actual_position - ray_source_actual_position;
            res.has_collision = false;

            float on_ray_proj = diff.dot(a->get_direction());
            // ray cast in other direction
            if (on_ray_proj < 0.0f) {
                res.has_collision = false;
                return res;
            }

            float l2 = diff.magnitude_squared();
            float d2 = l2 - on_ray_proj * on_ray_proj;
            float r2 = b->get_radius() * b->get_radius();
            res.has_collision = d2 < r2;
            if (res.has_collision) {
                float on_ray_proj_pen2 = r2 - d2;
                res.collision_depth = -1.0f * (on_ray_proj - sqrtf(on_ray_proj_pen2));
                res.a = a->get_source() + ta.position;
                res.b = ray_source_actual_position - a->get_direction() * res.collision_depth;
                res.normal = (res.b - res.a).normalized();
            }
            return res;
        }

        collision_point ray_ray_collision(const transform &ta, const RayCollider* a, const transform &tb, const RayCollider *b)
        {
            return collision_point();
        }
    }
}
