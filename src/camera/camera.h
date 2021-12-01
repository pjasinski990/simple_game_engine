#pragma once

#include "../math/vec3.h"
#include "../math/mat4.h"

namespace mrld
{
    class Window;
    class Camera
    {
    public:
        Camera(const Window *window, const vec3 &eye_position, const vec3 &target_position, const vec3 &up);
        virtual ~Camera() = default;
        virtual void update() {}

        inline void go_up(float dt) { _eye += _world_up * dt * _speed; }
        inline void go_down(float dt) { _eye -= _world_up * dt *_speed; }
        inline void go_forward(float dt) { _eye += _direction * dt *_speed; }
        inline void go_backward(float dt) { _eye -= _direction * dt *_speed; }
        inline void go_right(float dt) { _eye += _right * dt *_speed; }
        inline void go_left(float dt) { _eye -=  _right * dt *_speed; }

        void update_view();
        inline const mat4& get_view() const { return _view; }
        inline const mat4& get_proj() const { return _proj; }

    protected:
        const Window *_window;
        vec3 _eye;
        vec3 _direction;
        vec3 _world_up;
        vec3 _up;
        vec3 _right;

        mat4 _view;
        mat4 _proj;

        float _speed = 0.3f;
    };
}
