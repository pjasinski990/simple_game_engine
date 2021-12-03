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
            if (!collision.a->is_fixed) {
                collision.a->t.position -= collision.coll_p.normal * collision.coll_p.collision_depth;
            }
            else {
                collision.b->t.position += collision.coll_p.normal * collision.coll_p.collision_depth;
            }
        }
    }
}
