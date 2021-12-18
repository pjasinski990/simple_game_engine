#include "../utils/logger.h"
#include "body.h"
#include "physics_engine.h"
#include "collisions/collider.h"
#include "collisions/colliders/sphere_collider.h"
#include "collisions/solver/solver.h"
#include "collisions/colliders/ray_collider.h"

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
        std::vector<collision> colls = detect_collisions(dt);
        solve_collisions(dt, colls);
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

    /**
     * @brief Should be called after external update of objects transform (updates state of object in physics engine)
     * @param o Body that was updated
     */
    void PhysicsEngine::update_object(const Body *o)
    {
        auto target = std::find(_objects.begin(), _objects.end(), o);
        if (target != _objects.end()) {
            uint32_t i = target - _objects.begin();
            _previous_state[i] = o->t;
            _current_state[i] = o->t;
        }
        else {
            Logger::log(LogLevel::WRN, "Not updating object %p in physics engine - not found", o);
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

    std::vector<collision> PhysicsEngine::shoot_ray(vec3 source, vec3 direction)
    {
        std::vector<collision> res;
        RayCollider test_collider(source, direction);
        transform t;
        for (Body *o : _objects) {
            if (!o->get_collider()) { continue; }
            collision_point coll = test_collider.check_collision(t, o->get_collider(), o->t);
            if (coll.has_collision) {
                res.emplace_back(o, nullptr, coll);
            }
        }
        return res;
    }

    void PhysicsEngine::update_dynamics(float dt)
    {
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            _previous_state[i] = _current_state[i];
        }

        apply_forces(dt);
        handle_floor_friction(dt);
        clip_velocities(dt);
    }

    void PhysicsEngine::apply_forces(float dt)
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
                vec3 gravity_dir = _gravity.normalized();

                if (fabs(props.velocity.dot(gravity_dir)) < _floor_detection_velocity_threshold) {
                    vec3 friction = props.velocity * props.mass * props.friction_d * _gravity.magnitude();
                    friction.x *= 1.0f - fabs(vec3(1.0f, 0.0f, 0.0f).dot(gravity_dir));
                    friction.y *= 1.0f - fabs(vec3(0.0f, 1.0f, 0.0f).dot(gravity_dir));
                    friction.z *= 1.0f - fabs(vec3(0.0f, 0.0f, 1.0f).dot(gravity_dir));
                    props.acceleration -= friction;
                }
            }
        }
    }

    void PhysicsEngine::clip_velocities(float dt)
    {
        for (uint32_t i = 0; i < _objects.size(); ++i) {
            physics_properties &props = _objects[i]->phys_properties;
            if (fabs(props.velocity.x) + fabs(props.velocity.z) < _velocity_clipping_threshold) {
                props.velocity.x = 0.0f;
                props.velocity.z = 0.0f;
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
                if (!_objects[i]->is_dynamic() && !_objects[j]->is_dynamic()) { continue; }
                collision_point coll = _objects[i]->get_collider()->check_collision(
                        _objects[i]->t,
                        _objects[j]->get_collider(),
                        _objects[j]->t);

                if (coll.has_collision) {
                    // Objects are stored as a base pointer, collision will be detected in a dispatched
                    // call with reversed arguments, thus the reversed order in emplace
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
