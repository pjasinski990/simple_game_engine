#pragma once

#include <unordered_map>
#include <vector>

#include <GLFW/glfw3.h>

#include <mrld/key_code.h>

namespace mrld
{
    class Window;
    class KeyboardHandler
    {
    public:
        /**
         * @param keys std::vector of KeyCodes that will be handled by this instance of KeyboardHandler.
         */
        KeyboardHandler(const std::vector<KeyCode> &keys);
        ~KeyboardHandler();
        bool is_key_down(KeyCode key) const;

    private:
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static std::vector<KeyboardHandler*> _instances;
        std::unordered_map<int, bool> _key_states;
    };
}
