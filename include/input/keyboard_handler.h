#ifndef MRLD_ENGINE_KEYBOARD_HANDLER_H
#define MRLD_ENGINE_KEYBOARD_HANDLER_H

#include <unordered_map>
#include <vector>

#include <GLFW/glfw3.h>

#include <input/key_code.h>

namespace mrld
{
    class Window;
    class KeyboardHandler
    {
    public:
        KeyboardHandler(const std::vector<KeyCode> &keys);
        ~KeyboardHandler();
        bool is_key_down(KeyCode key) const;

    private:
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static std::vector<KeyboardHandler*> _instances;
        std::unordered_map<int, bool> _key_states;
    };
}

#endif //MRLD_ENGINE_KEYBOARD_HANDLER_H
