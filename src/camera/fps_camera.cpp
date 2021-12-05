#include <cmath>

#include <GLFW/glfw3.h>

#include "fps_camera.h"
#include "../window/window.h"
#include "../math/math_util.h"

namespace mrld
{
    FPSCamera::FPSCamera(const Window *window, const vec3 &eye_position, const vec3 &target_position, const vec3 &up, float aspect_ratio, float z_near, float z_far, float fov)
            : Camera(window, eye_position, target_position, up)
            , _mouse_handler(std::vector<MouseButton>())
            , _last_x{0.0f}
            , _last_y{0.0f}
            , _yaw{math_constants::pi}
            , _pitch{0.0f}
            , _ratio{aspect_ratio}
            , _z_near{z_near}
            , _z_far{z_far}
            , _fov{fov}
            , _cursor_enabled{true}
            , _first_mouse_update{true}
    {
        _proj = mat4::perspective(_ratio, _fov, _z_near, _z_far);
        update_view();
    }

    void FPSCamera::update()
    {
        if (_cursor_enabled) {
            return;
        }

        const float mouse_x = _mouse_handler.get_x();
        const float mouse_y = _mouse_handler.get_y();
        if (_first_mouse_update) {
            _first_mouse_update = false;
            _last_x = mouse_x;
            _last_y = mouse_y;
        }
        const float delta_x = _last_x - mouse_x;
        const float delta_y = _last_y - mouse_y;

        _yaw +=  delta_x * _mouse_sensitivity;
        _pitch += delta_y * _mouse_sensitivity;
        if (_pitch < -math_constants::pi2) {
            _pitch = -math_constants::pi2 + math_constants::epsilon;
        }
        else if (_pitch > math_constants::pi2) {
            _pitch = math_constants::pi2 - math_constants::epsilon;
        }

        _last_x = mouse_x;
        _last_y = mouse_y;

        vec3 direction;
        direction.z = cosf(_yaw) * cosf(_pitch);
        direction.y = sinf(_pitch);
        direction.x = sinf(_yaw) * cosf(_pitch);
        _direction = direction.normalized();
        update_view();
    }

    void FPSCamera::set_cursor_disabled()
    {
        _cursor_enabled = false;
        glfwSetCursorPos(_window->get_glfw_window(), _window->get_width() / 2.0, _window->get_height() / 2.0);
        glfwSetInputMode(_window->get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void FPSCamera::set_cursor_enabled()
    {
        _cursor_enabled = true;
        _first_mouse_update = true;
        glfwSetInputMode(_window->get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void FPSCamera::toggle_cursor_enabled()
    {
        if (_cursor_enabled) {
            set_cursor_disabled();
        }
        else {
            set_cursor_enabled();
        }
    }
}
