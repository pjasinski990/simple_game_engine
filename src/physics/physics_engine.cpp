#include "physics_engine.h"
#include "../utils/logger.h"
#include "object.h"
#include "../math/vec3.h"
#include "transform.h"

namespace mrld
{
    PhysicsEngine::PhysicsEngine()
    : _gravity(0.0f, -9.81f, 0.0f)
    {
        /* no-op */
    }

    void PhysicsEngine::step(float dt)
    {
        for (Object *o : _objects) {
            physics_properties &props = o->get_properties();
            props.acceleration += _gravity * props.mass;
            props.velocity += props.acceleration / props.mass * dt;
            props.position += props.velocity * dt;
            props.acceleration = vec3();

            o->update();
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
}