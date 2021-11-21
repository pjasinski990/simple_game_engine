#pragma once

#include "../../math/vec3.h"
#include "../../math/mat4.h"

namespace mrld
{
    class Window;
    class Camera
    {
    public:
        Camera(const Window *window, const vec3 &eye_position, const vec3 &target_position, const vec3 &up);
        virtual ~Camera() = default;
        virtual void update() {}

        inline void go_up() { _eye += _world_up * _speed; }
        inline void go_down() { _eye -= _world_up * _speed; }
        inline void go_forward() { _eye += _direction * _speed; }
        inline void go_backward() { _eye -= _direction * _speed; }
        inline void go_right() { _eye += _right * _speed; }
        inline void go_left() { _eye -=  _right * _speed; }

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

        float _speed = 0.02f;
    };
}
