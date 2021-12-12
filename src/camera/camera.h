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
        virtual void update() = 0;

        inline vec3 get_right() { return _right; }
        inline vec3 get_left() { return -1.0f * _right; }
        inline vec3 get_front() { return _world_up.cross(_right).normalized(); }
        inline vec3 get_back() { return -1.0f * get_front(); }
        inline vec3 get_up() { return _world_up; }
        inline vec3 get_down() { return -1.0f * _world_up; }

        inline void go_up(float dt) { _eye += get_up() * dt * _speed; }
        inline void go_down(float dt) { _eye += get_down() * dt *_speed; }
        inline void go_forward(float dt) { _eye += get_front() * dt *_speed; }
        inline void go_backward(float dt) { _eye += get_back() * dt *_speed; }
        inline void go_right(float dt) { _eye += get_right() * dt *_speed; }
        inline void go_left(float dt) { _eye += get_left() * dt *_speed; }

        void update_view();
        inline void set_view(const mat4 &view) { _view = view; }
        inline const mat4& get_view() const { return _view; }
        inline void set_proj(const mat4 &proj) { _proj = proj; }
        inline const mat4& get_proj() const { return _proj; }

        inline const vec3& get_position() const { return _eye; }
        inline void set_position(const vec3 &pos) { _eye = pos; }
        inline const vec3& get_direction() const { return _direction; }
        inline void set_direction(const vec3 &dir) { _direction = dir; }

    protected:
        const Window *_window;
        vec3 _eye;
        vec3 _direction;
        vec3 _world_up;
        vec3 _up;
        vec3 _right;

        mat4 _view;
        mat4 _proj;

        const float _speed = 10.0f;
    };
}
