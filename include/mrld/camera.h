#pragma once

#include <mrld/vec3.h>
#include <mrld/mat4.h>

namespace mrld
{
    class Camera
    {
    public:
        Camera(const mrld::vec3 &eye_position, const mrld::vec3 &target_position, float aspect_ratio, float z_near, float z_far, float fov);
        void translate(const vec3 &delta);
        void move_to(const vec3 &position);
//        void rotate(const vec3 &angle /* or maybe quat? */);
        mrld::mat4 look_at(const vec3 &position);
    private:
        mrld::vec3 _eye;
        mrld::vec3 _target;
        mrld::vec3 _up;

        float _z_near;
        float _z_far;
        float _ratio;
        float _fov;
    };
}
