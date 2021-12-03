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

            const float m = std::max(2.0f - collision.a->is_fixed - collision.b->is_fixed, 1.0f);
            const float a_displacement_ratio = (1.0f - collision.a->is_fixed) * m;
            const float b_displacement_ratio = (1.0f - collision.b->is_fixed) * m;
            collision.a->t.position -= collision.coll_p.normal * collision.coll_p.collision_depth * a_displacement_ratio;
            collision.b->t.position += collision.coll_p.normal * collision.coll_p.collision_depth * b_displacement_ratio;
        }
    }
}
