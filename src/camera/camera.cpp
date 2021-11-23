#include "camera.h"

namespace mrld
{
    Camera::Camera(const Window *window, const vec3 &eye_position, const vec3 &target_position, const vec3 &up)
    : _window{window}
    , _eye{eye_position}
    , _direction{(target_position - _eye).normalized()}
    , _world_up{up.normalized()}
    , _right{_direction.cross(_world_up).normalized()}
    {
        _view = mat4::identity();
        update_view();
    }

    void Camera::update_view()
    {
        _right = _direction.cross(_world_up).normalized();
        _up = _right.cross(_direction).normalized();

        _view.at(0, 0) = _right.x;
        _view.at(0, 1) = _right.y;
        _view.at(0, 2) = _right.z;

        _view.at(1, 0) = _up.x;
        _view.at(1, 1) = _up.y;
        _view.at(1, 2) = _up.z;

        _view.at(2, 0) = -_direction.x;
        _view.at(2, 1) = -_direction.y;
        _view.at(2, 2) = -_direction.z;

        _view.at(0, 3) = -_right.dot(_eye);
        _view.at(1, 3) = -_up.dot(_eye);
        _view.at(2, 3) = _direction.dot(_eye);
    }
}
