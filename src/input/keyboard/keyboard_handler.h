#pragma once

#include <unordered_map>
#include <vector>

#include "../key_code.h"

namespace mrld
{
    class Window;
    class KeyboardHandler
    {
    public:
        KeyboardHandler(const std::vector<KeyCode> &keys);
        ~KeyboardHandler();
        KeyboardHandler(const KeyboardHandler& o) = delete;
        KeyboardHandler& operator=(const KeyboardHandler &o) = delete;
        KeyboardHandler(KeyboardHandler &&o) = delete;
        KeyboardHandler& operator=(KeyboardHandler &&o) = delete;

        bool is_key_down(KeyCode key) const;
        void debounce(KeyCode key);

    private:

        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static std::vector<KeyboardHandler*> _instances;
        std::unordered_map<KeyCode, bool> _key_states;
    };
}
