#include "camera.h"
#include "../math/quaternion.h"

namespace mrld
{
    Camera::Camera(const vec3 &eye_position, const vec3 &target_position, const vec3 &up, float aspect_ratio, float z_near, float z_far, float fov)
    : _eye{eye_position}
    , _direction{(target_position - _eye).normalized()}
    , _up{up}
    , _right{_direction.cross(up).normalized()}
    , _ratio{aspect_ratio}
    , _z_near{z_near}
    , _z_far{z_far}
    , _fov{fov}
    {
        _up = _up.normalized();
        _proj = mrld::mat4::perspective(aspect_ratio, fov, z_near, z_far);
        update();
    }

    void Camera::update()
    {
        _up = _right.cross(_direction).normalized();

        _view = mat4::identity();
        _view.at(0, 0) = -_right.x;
        _view.at(1, 0) = -_right.y;
        _view.at(2, 0) = -_right.z;

        _view.at(0, 1) = _up.x;
        _view.at(1, 1) = _up.y;
        _view.at(2, 1) = _up.z;

        _view.at(0, 2) = -_direction.x;
        _view.at(1, 2) = -_direction.y;
        _view.at(2, 2) = -_direction.z;

        _view.at(0, 3) = -_right.dot(_eye);
        _view.at(1, 3) = -_up.dot(_eye);
        _view.at(2, 3) =  _direction.dot(_eye);
    }
}
