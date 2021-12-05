#include "../utils/logger.h"
#include "body.h"
#include "physics_engine.h"
#include "collisions/collider.h"
#include "collisions/colliders/sphere_collider.h"
#include "collisions/solver/solver.h"

namespace mrld
{
    PhysicsEngine::PhysicsEngine()
    : _gravity(0.0f, -9.81f, 0.0f)
    {
        /* no-op */
    }

    void PhysicsEngine::step(float dt)
    {
        update_dynamics(dt);
        std::vector<collision> c = detect_collisions(dt);
        solve_collisions(dt, c);
    }

    void PhysicsEngine::interpolate_previous_state(float ratio)
    {
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            vec3 position_path = _current_state[i].position - _previous_state[i].position;
            _objects[i]->t.position = _previous_state[i].position + position_path * ratio;
            _objects[i]->update_model();
        }
    }

    void PhysicsEngine::update_models()
    {
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            _objects[i]->t = _current_state[i];
            _objects[i]->update_model();
        }
    }

    void PhysicsEngine::add(Body *o)
    {
        _objects.push_back(o);
        _previous_state.push_back(o->t);
        _current_state.push_back(o->t);
    }

    void PhysicsEngine::remove(Body *o)
    {
        auto target = std::find(_objects.begin(), _objects.end(), o);
        if (target != _objects.end()) {
            uint32_t i = target - _objects.begin();
            _previous_state.erase(_previous_state.begin() + i);
            _current_state.erase(_current_state.begin() + i);
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

    void PhysicsEngine::update_dynamics(float dt)
    {
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            _previous_state[i] = _current_state[i];
        }

        apply_gravity(dt);
        handle_floor_friction(dt);
    }

    void PhysicsEngine::apply_gravity(float dt)
    {
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            if (_objects[i]->is_dynamic()) {
                physics_properties &props = _objects[i]->phys_properties;
                props.acceleration += _gravity * props.mass;
                props.velocity += props.acceleration / props.mass * dt;
                _objects[i]->t.position += props.velocity * dt;
                props.acceleration = vec3();
            }
        }
    }

    void PhysicsEngine::handle_floor_friction(float dt)
    {
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            if (_objects[i]->is_dynamic()) {
                physics_properties &props = _objects[i]->phys_properties;

                if (fabs(props.velocity.x) < _velocity_clipping_threshold) {
                    props.velocity.x = 0.0f;
                }
                if (fabs(props.velocity.z) < _velocity_clipping_threshold) {
                    props.velocity.z = 0.0f;
                }

                if (fabs(props.velocity.dot(_gravity.normalized())) < _floor_detection_velocity_threshold) {
                    props.acceleration += props.velocity * props.mass * props.friction_d * _gravity.magnitude() * -1.0f;
                }
            }
        }
    }

        std::vector<collision> PhysicsEngine::detect_collisions(float dt)
    {
        std::vector<collision> collisions;
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            for (uint32_t j = i + 1; j < _objects.size(); ++j) {
                if (_objects[i] == _objects[j]) { continue; }
                if (!_objects[i]->get_collider() || !_objects[j]->get_collider()) { continue; }
                collision_point coll = _objects[i]->get_collider()->check_collision(
                        _objects[i]->t,
                        _objects[j]->get_collider(),
                        _objects[j]->t);

                if (coll.has_collision) {
                    // Objects are stored as a base pointer, collision will be detected in a dispatched call with reversed arguments
                    collisions.emplace_back(_objects[j], _objects[i], coll);
                }
            }
        }
        return collisions;
    }

    void PhysicsEngine::solve_collisions(float dt, std::vector<collision> &collisions)
    {
        for (Solver* s : _solvers) {
            s->solve(collisions, dt);
        }
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            _current_state[i].position = _objects[i]->t.position;
        }
    }
}
