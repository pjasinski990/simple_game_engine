#pragma once

#include "solver.h"

namespace mrld
{
    class PositionCorrectionSolver: public Solver
    {
    public:
        void solve(std::vector<collision> &collisions, float dt) override;
    private:

    };
}
