#pragma once

#include "../math/vec3.h"
#include "../math/mat4.h"

namespace mrld
{
    struct quat;
    class Camera
    {
    public:
        Camera(const vec3 &eye_position, const vec3 &target_position, const vec3 &up, float aspect_ratio, float z_near, float z_far, float fov);
        void update();

        inline void go_up() { _eye += _up * _speed; }
        inline void go_down() { _eye -= _up * _speed; }
        inline void go_forward() { _eye += _direction * _speed; }
        inline void go_backward() { _eye -= _direction * _speed; }
        inline void go_right() { _eye += _right * _speed; }
        inline void go_left() { _eye -=  _right * _speed; }

        inline const mat4& get_view() const { return _view; }
        inline const mat4& get_proj() const { return _proj; }

    private:
        mrld::vec3 _eye;
        mrld::vec3 _direction;
        mrld::vec3 _up;
        mrld::vec3 _right;

        mrld::mat4 _view;
        mrld::mat4 _proj;

        float _z_near;
        float _z_far;
        float _ratio;
        float _fov;
        float _speed = 0.02f;
    };
}
