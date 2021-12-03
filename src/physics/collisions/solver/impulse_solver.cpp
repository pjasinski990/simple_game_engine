#include "impulse_solver.h"
#include "../../object.h"
#include "../../../utils/logger.h"

namespace mrld
{
    void ImpulseSolver::solve(std::vector<collision> &collisions, float dt)
    {
        for (collision &collision : collisions) {
            float inv_mass_sum = collision.a->phys_properties.mass_inv + collision.b->phys_properties.mass_inv;
            if (inv_mass_sum == 0.0f) {
                Logger::log(LogLevel::WRN, "Request for solving of collision between two fixed objects detected");
                return;
            }
            else {
                inv_mass_sum = collision.a->phys_properties.mass_inv + collision.b->phys_properties.mass_inv;
            }
            const float bounciness = std::min(collision.a->phys_properties.bounciness, collision.b->phys_properties.bounciness);

            for (uint32_t i = 0; i < _n_iterations; ++i) {
                const vec3 v_rel = collision.b->phys_properties.velocity - collision.a->phys_properties.velocity;
                const float v_on_normal = v_rel.dot(collision.coll_p.normal);
                if (v_on_normal > 0.0f) { continue; } // bodies moving away

                float impulse_a = 1.0f * (1.0f + bounciness) * v_on_normal / inv_mass_sum;
                float impulse_b = -1.0f * impulse_a;
                if (!collision.a->is_fixed) {
                    collision.a->phys_properties.velocity += collision.coll_p.normal * impulse_a * collision.a->phys_properties.mass_inv;
                }
                if (!collision.b->is_fixed) {
                    collision.b->phys_properties.velocity += collision.coll_p.normal * impulse_b * collision.b->phys_properties.mass_inv;
                }
            }
        }
    }
}
