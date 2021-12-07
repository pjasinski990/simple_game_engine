#pragma once

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace mrld
{
    class Window
    {
    public:
        Window(const char* name, uint16_t width, uint16_t height);
        ~Window();
        void clear() const;
        void update() const;
        bool should_close() const;
        inline uint16_t get_width() const {return _width;}
        inline uint16_t get_height() const {return _height;}
        inline GLFWwindow *get_glfw_window() const { return _window; }
        inline void close() { glfwSetWindowShouldClose(_window, GL_TRUE); }

    private:
        GLFWwindow* _window;
        const char* _name;
        uint16_t _width;
        uint16_t _height;
    };

    void on_window_resize(GLFWwindow *window, int width, int height);
}
