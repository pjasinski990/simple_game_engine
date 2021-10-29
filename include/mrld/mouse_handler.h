#ifndef MRLD_ENGINE_MOUSE_HANDLER_H
#define MRLD_ENGINE_MOUSE_HANDLER_H

#include <vector>
#include <unordered_map>

struct GLFWwindow;

namespace mrld
{
    class MouseHandler
    {
    public:
        MouseHandler(const std::vector<MouseButton> &mouse_buttons);
        ~MouseHandler();
        inline float get_x() const { return _x_pos; }
        inline float get_y() const { return _y_pos; }
        inline float get_scroll_x() const { return _x_scroll; }
        inline float get_scroll_y() const { return _y_scroll; }
        inline bool is_button_down(MouseButton button) const { return _mouse_button_states.at(static_cast<int>(button)); }

    private:
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        static void cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos);
        static void scroll_callback(GLFWwindow *window, double x_offset, double y_offset);
        static std::vector<MouseHandler*> _instances;
        std::unordered_map<int, bool> _mouse_button_states;
        float _x_pos;
        float _y_pos;
        float _x_scroll;
        float _y_scroll;
    };
}
#endif //MRLD_ENGINE_MOUSE_HANDLER_H
