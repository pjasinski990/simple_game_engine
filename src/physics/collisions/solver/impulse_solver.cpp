#include <unordered_map>

#include "../../body.h"
#include "impulse_solver.h"

namespace mrld
{
    void ImpulseSolver::solve(std::vector<collision> &cols, float dt)
    {
        for (uint32_t i = 0; i < _n_iterations; ++i) {
            apply_impulse(cols);
        }
    }

    void ImpulseSolver::apply_impulse(std::vector<collision> &collisions)
    {
        std::unordered_map<Body*, vec3> velocity_changes;
        for (collision &col : collisions) {
            Body *body = col.a;
            Body *other = col.b;
            float inv_mass_sum = body->phys_properties.mass_inv + other->phys_properties.mass_inv;
            if (inv_mass_sum == 0.0f) {
                return;
            }
            const float bounciness = body->phys_properties.bounciness * other->phys_properties.bounciness;
            const vec3 v_rel = other->phys_properties.velocity - body->phys_properties.velocity;
            const float v_on_normal = v_rel.dot(col.coll_p.normal);
            if (v_on_normal < 0.0f) { continue; } // bodies moving away

            float impulse_a = (1.0f + bounciness) * v_on_normal / inv_mass_sum;
            float impulse_b = -1.0f * impulse_a;
            if (body->is_dynamic()) {
                velocity_changes[body] += col.coll_p.normal * impulse_a * body->phys_properties.mass_inv;
            }
            if (other->is_dynamic()) {
                velocity_changes[other] += col.coll_p.normal * impulse_b * other->phys_properties.mass_inv;
            }
        }

        for (auto &[body, change] : velocity_changes) {
            body->phys_properties.velocity += change;
        }
    }
}
