#include <mrld/camera.h>

namespace mrld
{
    Camera::Camera(const vec3 &eye_position, const vec3 &target_position, float aspect_ratio, float z_near, float z_far, float fov):
            _eye{eye_position}, _target{target_position}, _ratio{aspect_ratio}, _z_near{z_near}, _z_far{z_far}, _fov{fov}
    {
        /* no-op */
    }

    void Camera::translate(const vec3 &delta)
    {
        _eye += delta;
    }

    void Camera::move_to(const vec3 &position)
    {
        _eye = position;
    }

    mat4 Camera::look_at(const vec3 &position)
    {
        mat4 res = mat4::identity();
        return mat4();
    }
}
