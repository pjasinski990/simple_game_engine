#ifndef MRLD_ENGINE_MOUSE_HANDLER_H
#define MRLD_ENGINE_MOUSE_HANDLER_H

#include <vector>
#include <unordered_map>

#include <window/window.h>

namespace mrld
{
    class MouseHandler
    {
    public:
        MouseHandler(const std::vector<MouseButton> &mouse_buttons);
        ~MouseHandler();
        inline double get_x() const { return _x_pos; }
        inline double get_y() const { return _y_pos; }
        double is_button_down(MouseButton button) const;

    private:
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        static void cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos);
        static std::vector<MouseHandler*> _instances;
        std::unordered_map<int, bool> _mouse_button_states;
        unsigned int _x_pos;
        unsigned int _y_pos;
    };
}
#endif //MRLD_ENGINE_MOUSE_HANDLER_H
