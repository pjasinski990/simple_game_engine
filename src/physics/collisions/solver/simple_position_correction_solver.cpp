#include "simple_position_correction_solver.h"
#include "../../rigidbody.h"
#include "../../../utils/logger.h"

namespace mrld
{
    void SimplePositionCorrectionSolver::solve(std::vector<collision> &collisions, float dt)
    {
        for (collision &collision : collisions) {
            const float a_dynamic = static_cast<float>(collision.a->is_dynamic());
            const float b_dynamic = static_cast<float>(collision.b->is_dynamic());
            if (a_dynamic + b_dynamic == 0.0f) {return;}

            const float m = std::max(a_dynamic + b_dynamic, 1.0f);
            const float a_displacement_ratio = a_dynamic / m;
            const float b_displacement_ratio = b_dynamic / m;
            collision.a->t.position += collision.coll_p.normal * collision.coll_p.collision_depth * a_displacement_ratio;
            collision.b->t.position -= collision.coll_p.normal * collision.coll_p.collision_depth * b_displacement_ratio;
        }
    }
}
