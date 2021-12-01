#pragma once

#include <vector>
#include "../math/vec3.h"

namespace mrld
{
    class Object;
    class Solver;
    class PhysicsEngine
    {
    public:
        PhysicsEngine();

        void step(float dt);
        void add(Object *o);
        void remove(Object *o);
        void add_solver(Solver *o);
        void remove_solver(Solver *o);
    private:
        vec3 _gravity;
        std::vector<Object*> _objects;
        std::vector<Solver*> _solvers;
    };
}