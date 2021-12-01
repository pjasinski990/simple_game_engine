#include "impulse_solver.h"
#include "../../object.h"
#include "../../../utils/logger.h"

namespace mrld
{
    void ImpulseSolver::solve(std::vector<collision> &collisions, float dt)
    {
        for (collision &collision : collisions) {
            if (collision.a->is_fixed && collision.b->is_fixed) {
                Logger::log(LogLevel::WRN, "Request for solving of collision between two fixed objects detected");
                return;
            }

            float mass_a = collision.a->phys_properties.mass;
            float mass_b = collision.b->phys_properties.mass;
            float inv_mass_sum;
            if (collision.a->is_fixed) {
                mass_a = 0.0f;
                inv_mass_sum = collision.b->phys_properties.mass_inv;
            }
            else if (collision.b->is_fixed) {
                mass_b = 0.0f;
                inv_mass_sum = collision.a->phys_properties.mass_inv;
            }
            else {
                inv_mass_sum = collision.a->phys_properties.mass_inv + collision.b->phys_properties.mass_inv;
            }
            const float bounciness = std::min(collision.a->phys_properties.bounciness, collision.b->phys_properties.bounciness);

            for (uint32_t i = 0; i < _n_iterations; ++i) {
                const vec3 v_rel = collision.b->phys_properties.velocity - collision.a->phys_properties.velocity;
                const float v_on_normal = v_rel.dot(collision.coll_p.normal);
                if (v_on_normal < 0.0f) { continue; } // bodies moving away

                float impulse_a = (1.0f + bounciness) * v_on_normal / inv_mass_sum;
                float impulse_b = -1.0f * (1.0f + bounciness) * v_on_normal / inv_mass_sum;
                collision.a->phys_properties.velocity += collision.coll_p.normal * impulse_a * mass_a;
                collision.b->phys_properties.velocity += collision.coll_p.normal * impulse_b * mass_b;
            }
        }
    }
}
