#pragma once

#include <unordered_set>

#include "solver.h"

namespace mrld
{
    class RecursivePositionCorrectionSolver: public Solver
    {
    public:
        void solve(std::vector<collision> &collisions, float dt) override;

    private:
        bool solve_body(
                Body *body,
                Body *previous_other,
                std::unordered_map<Body*, vec3> &body_to_displacement,
                std::unordered_map<Body*, std::vector<collision*>> &body_to_contacts,
                std::unordered_set<collision*> &affected);
        void solve_all(std::vector<collision*> &collisions);

        const float _acceptable_collision_depth = 0.05f;
    };
}
