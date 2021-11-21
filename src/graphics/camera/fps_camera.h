#pragma once

#include "../../math/vec3.h"
#include "../../math/mat4.h"
#include "camera.h"
#include "../../input/mouse/mouse_handler.h"

namespace mrld
{
    class FPSCamera: public Camera
    {
    public:
        FPSCamera(const Window *window, const vec3 &eye_position, const vec3 &target_position, const vec3 &up, float aspect_ratio, float z_near, float z_far, float fov);
        void update() override;
        void set_cursor_disabled();
        void set_cursor_enabled();
        void toggle_cursor_enabled();
    private:
        MouseHandler _mouse_handler;
        float _last_x;
        float _last_y;
        float _yaw;
        float _pitch;

        float _z_near;
        float _z_far;
        float _ratio;
        float _fov;
        float _mouse_sensitivity = 0.001f;
        bool _cursor_enabled;
        bool _first_mouse_update;
    };
}
