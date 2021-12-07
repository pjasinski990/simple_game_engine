#pragma once

#include "camera.h"

namespace mrld
{
    struct vec3;
    class OrthographicCamera: public Camera
    {
    public:
        OrthographicCamera(const Window *window);
        OrthographicCamera(const Window *window, float left, float right, float bottom, float top, float near, float far);
        OrthographicCamera(const Window *window, const vec3 &eye_position, const vec3 &target_position, const vec3 &up);
        void update() override {};
    private:
    };

}
