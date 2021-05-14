#include <input/key_code.h>
#include <input/mouse_handler.h>

std::vector<mrld::MouseHandler*> mrld::MouseHandler::_instances;

mrld::MouseHandler::MouseHandler(const std::vector<MouseButton> &mouse_buttons)
{
    _instances.push_back(this);
    _mouse_button_states.reserve(mouse_buttons.size());
    for (auto k : mouse_buttons) {
        _mouse_button_states[static_cast<int>(k)] = false;
    }

    glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
    glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
}

mrld::MouseHandler::~MouseHandler()
{
    std::vector<MouseHandler*>::iterator it = std::find(std::begin(_instances), std::end(_instances), this);
    _instances.erase(it);
}

void mrld::MouseHandler::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    for (auto q : _instances) {
        std::unordered_map<int, bool>::iterator it = q->_mouse_button_states.find(button);
        if (it != q->_mouse_button_states.end()) {
            q->_mouse_button_states[button] = action != GLFW_RELEASE;
        }
    }
}

void mrld::MouseHandler::cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos)
{
    for (auto q : _instances) {
        q->_x_pos = x_pos;
        q-> _y_pos = y_pos;
    }
}

double mrld::MouseHandler::is_button_down(mrld::MouseButton button) const
{
    return _mouse_button_states.at(static_cast<int>(button));
}

