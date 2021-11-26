#pragma once

#include <vector>
#include "../math/vec3.h"

namespace mrld
{
    class Object;
    class PhysicsEngine
    {
    public:
        PhysicsEngine();

        void step(float dt);
        void add(Object *o);
        void remove(Object *o);
    private:
        vec3 _gravity;
        std::vector<Object*> _objects;
    };
}