#include "orthographic_camera.h"
#include "../graphics/shader/shader.h"
#include "../window/window.h"

namespace mrld
{
    OrthographicCamera::OrthographicCamera(const Window *window, float left, float right, float bottom, float top, float near, float far)
    : Camera(window, vec3(0.0f, 0.0f, 0.5f), vec3(), vec3(0.0f, 1.0f, 0.0f))
    {
        _proj = mat4::orthographic(left, right, bottom, top, near, far);
        update_view();
    }

    OrthographicCamera::OrthographicCamera(const Window *window)
    : OrthographicCamera(window, -1, 1, -1, 1, -1, 1)
    {
        /* no-op */
    }

    OrthographicCamera::OrthographicCamera(const Window *window, const vec3 &eye_position, const vec3 &target_position, const vec3 &up)
    : Camera(window, eye_position, target_position, up)
    {
        _proj = mat4::orthographic(-1, 1, -1, 1, -1, 1);
        update_view();
    }

}
