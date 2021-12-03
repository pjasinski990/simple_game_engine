#pragma once

#include "collision_point.h"

namespace mrld
{
    class Body;
    struct collision
    {
        collision(Body *o1, Body *o2, collision_point &coll): a{o1}, b{o2}, coll_p{coll} {}
        Body *a;
        Body *b;
        collision_point coll_p;
    };
}
