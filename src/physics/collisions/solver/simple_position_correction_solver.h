#pragma once

#include "solver.h"

namespace mrld
{
    class SimplePositionCorrectionSolver: public Solver
    {
    public:
        void solve(std::vector<collision> &collisions, float dt) override;
    private:

    };
}
