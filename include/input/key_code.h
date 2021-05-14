#ifndef MRLD_ENGINE_KEY_CODE_H
#define MRLD_ENGINE_KEY_CODE_H

#include <GLFW/glfw3.h>

namespace mrld
{
    enum MouseButton {
        BUTTON_LEFT = GLFW_MOUSE_BUTTON_1,
        BUTTON_RIGHT = GLFW_MOUSE_BUTTON_2,
        BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_3,
        BUTTON_4 = GLFW_MOUSE_BUTTON_4,
        BUTTON_5 = GLFW_MOUSE_BUTTON_5,
        BUTTON_6 = GLFW_MOUSE_BUTTON_6,
        BUTTON_7 = GLFW_MOUSE_BUTTON_7,
        BUTTON_8 = GLFW_MOUSE_BUTTON_8,
    };

    enum KeyCode {
        W = GLFW_KEY_W,
        S = GLFW_KEY_S,
        A = GLFW_KEY_A,
        D = GLFW_KEY_D,
    };
}

#endif //MRLD_ENGINE_KEY_CODE_H
