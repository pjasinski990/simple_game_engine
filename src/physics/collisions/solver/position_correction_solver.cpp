#include "position_correction_solver.h"
#include "../../object.h"
#include "../../../utils/logger.h"

namespace mrld
{
    void PositionCorrectionSolver::solve(std::vector<collision> &collisions, float dt)
    {
        for (collision &collision : collisions) {
            if (collision.a->is_fixed && collision.b->is_fixed) {
                Logger::log(LogLevel::WRN, "Request for solving of collision between two fixed objects detected");
                return;
            }

            const vec3 v_rel = collision.b->phys_properties.velocity - collision.a->phys_properties.velocity;
            const float v_on_normal = v_rel.dot(collision.coll_p.normal);
            if (v_on_normal < 0.0f) { return; } // bodies moving away

            if (!collision.a->is_fixed) {
                collision.a->t.position -= collision.coll_p.normal * collision.coll_p.collision_depth;
            }
            if (!collision.b->is_fixed) {
                collision.b->t.position += collision.coll_p.normal * collision.coll_p.collision_depth;
            }
        }
    }
}
