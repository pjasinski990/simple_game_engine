#include <algorithm>

#include "mouse_handler.h"
#include "../key_code.h"

namespace mrld
{
    std::vector<MouseHandler *> MouseHandler::_instances;

    MouseHandler::MouseHandler(const std::vector<MouseButton> &mouse_buttons)
    {
        _instances.push_back(this);
        _mouse_button_states.reserve(mouse_buttons.size());
        for (auto k : mouse_buttons) {
            _mouse_button_states[static_cast<int>(k)] = false;
        }

        glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
        glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
        glfwSetScrollCallback(glfwGetCurrentContext(), scroll_callback);
    }

    MouseHandler::~MouseHandler()
    {
        std::vector<MouseHandler *>::iterator it = std::find(std::begin(_instances), std::end(_instances), this);
        _instances.erase(it);
    }

    void MouseHandler::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        for (auto q : _instances) {
            std::unordered_map<int, bool>::iterator it = q->_mouse_button_states.find(button);
            if (it != q->_mouse_button_states.end()) {
                q->_mouse_button_states[button] = action != GLFW_RELEASE;
            }
        }
    }

    void MouseHandler::cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos)
    {
        for (auto q : _instances) {
            q->_x_pos = static_cast<float>(x_pos);
            q->_y_pos = static_cast<float>(y_pos);
        }
    }

    void MouseHandler::scroll_callback(GLFWwindow *window, double x_offset, double y_offset)
    {
        for (auto q : _instances) {
            q->_x_scroll = static_cast<float>(x_offset);
            q->_y_scroll = static_cast<float>(y_offset);
        }
    }
}
