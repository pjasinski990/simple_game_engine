#include <algorithm>

#include "keyboard_handler.h"

namespace mrld
{
    std::vector<KeyboardHandler *> KeyboardHandler::_instances;

    KeyboardHandler::KeyboardHandler(const std::vector<KeyCode> &keys)
    {
        _instances.push_back(this);
        _key_states.reserve(keys.size());
        for (auto k : keys) {
            _key_states[static_cast<int>(k)] = false;
        }
        glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
    }

    KeyboardHandler::~KeyboardHandler()
    {
        std::vector<KeyboardHandler *>::iterator it = std::find(std::begin(_instances), std::end(_instances), this);
        _instances.erase(it);
    }

    void KeyboardHandler::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        for (auto q : _instances) {
            std::unordered_map<int, bool>::iterator it = q->_key_states.find(key);
            if (it != q->_key_states.end()) {
                q->_key_states[key] = action != GLFW_RELEASE;
            }
        }
    }

    bool KeyboardHandler::is_key_down(KeyCode key) const
    {
        return _key_states.at(static_cast<int>(key));
    }
}
