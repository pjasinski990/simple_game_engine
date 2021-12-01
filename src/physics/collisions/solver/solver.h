#pragma once

#include <vector>
#include "../collision.h"

namespace mrld
{
    class Solver
    {
    public:
        virtual void solve(std::vector<collision> &collisions, float dt) = 0;
    protected:

    };
}
