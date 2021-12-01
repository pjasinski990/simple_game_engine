#pragma once

#include "collision_point.h"

namespace mrld
{
    class Object;
    struct collision
    {
        collision(Object *o1, Object *o2, collision_point &coll): a{o1}, b{o2}, coll_p{coll} {}
        Object *a;
        Object *b;
        collision_point coll_p;
    };
}
