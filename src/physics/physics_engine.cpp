#include "../utils/logger.h"
#include "object.h"
#include "physics_engine.h"
#include "collisions/collision_point.h"
#include "collisions/collider.h"
#include "collisions/colliders/sphere_collider.h"
#include "collisions/solver/solver.h"
#include "collisions/collision.h"

namespace mrld
{
    PhysicsEngine::PhysicsEngine()
    : _gravity(0.0f, -9.81f, 0.0f)
    {
        /* no-op */
    }

    void PhysicsEngine::step(float dt)
    {
        std::vector<collision> collisions;
        for (Object *o : _objects) {
            if (o->has_physics) {
                if (!o->is_fixed) {
                    // Update dynamics
                    physics_properties &props = o->phys_properties;
                    props.acceleration += _gravity * props.mass;
                    props.velocity += props.acceleration / props.mass * dt;
                    o->t.position += props.velocity * dt;
                    props.acceleration = vec3();

                    o->update();
                }

                // Detect collisions
                // TODO rewrite this and solvers to use multiple collision points for each colliding body
                for (Object *o2 : _objects) {
                    if (o == o2) { continue; }                                      // Skip self-collision
                    if (!o->get_collider() || !o2->get_collider()) { continue; }    // Both have collider

                    collision_point coll = o->get_collider()->check_collision(o->t, o2->get_collider(), o2->t);
                    if (coll.has_collision) {
                        collisions.emplace_back(o, o2, coll);
                    }
                }

                // Solve collisions
                for (Solver* s : _solvers) {
                    s->solve(collisions, dt);
                }
            }
        }
    }

    void PhysicsEngine::add(Object *o)
    {
        _objects.push_back(o);
    }

    void PhysicsEngine::remove(Object *o)
    {
        auto target = std::find(_objects.begin(), _objects.end(), o);
        if (target != _objects.end()) {
            _objects.erase(target);
        }
        else {
            Logger::log(LogLevel::WRN, "Not removing object from physics engine - not found");
        }
    }

    void PhysicsEngine::add_solver(Solver *o)
    {
        _solvers.push_back(o);
    }

    void PhysicsEngine::remove_solver(Solver *o)
    {
        auto target = std::find(_solvers.begin(), _solvers.end(), o);
        if (target != _solvers.end()) {
            _solvers.erase(target);
        }
        else {
            Logger::log(LogLevel::WRN, "Not removing solver from physics engine - not found");
        }
    }
}
