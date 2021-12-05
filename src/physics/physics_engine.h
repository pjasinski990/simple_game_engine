#pragma once

#include <vector>
#include "../math/vec3.h"
#include "collisions/collision.h"

namespace mrld
{
    class Body;
    class Solver;
    class PhysicsEngine
    {
    public:
        PhysicsEngine();

        // TODO add friction and angular physics
        void step(float dt);
        void interpolate_previous_state(float ratio);
        void update_models();
        void add(Body *o);
        void remove(Body *o);
        void add_solver(Solver *o);
        void remove_solver(Solver *o);
    private:
        void update_dynamics(float dt);
        void apply_gravity(float dt);
        void handle_floor_friction(float dt);

        std::vector<collision> detect_collisions(float dt);
        void solve_collisions(float dt, std::vector<collision> &collisions);

        const float _velocity_clipping_threshold = 0.2f;
        const float _floor_detection_velocity_threshold = 0.2f;

        vec3 _gravity;
        std::vector<Body*> _objects;
        std::vector<transform> _previous_state;
        std::vector<transform> _current_state;
        std::vector<Solver*> _solvers;
    };
}