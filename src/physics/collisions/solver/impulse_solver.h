#pragma once

#include "solver.h"

namespace mrld
{
    class ImpulseSolver: public Solver
    {
    public:
        void solve(std::vector<collision> &collisions, float dt) override;
    private:
        const uint32_t _n_iterations = 8u;
    };
}
