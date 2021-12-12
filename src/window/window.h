#pragma once

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../math/vec3.h"

struct GLFWwindow;

namespace mrld
{
    class Window
    {
    public:
        Window(const char* name, uint32_t width, uint32_t height);
        ~Window();
        void clear() const;
        void update() const;
        bool should_close() const;
        inline void set_clear_color(const mrld::vec3 &color) { glClearColor(color.x, color.y, color.z, 1.0f); }
        inline uint32_t get_width() const {return _width;}
        inline uint32_t get_height() const {return _height;}
        inline GLFWwindow *get_glfw_window() const { return _window; }
        inline void close() { glfwSetWindowShouldClose(_window, GL_TRUE); }

    private:
        GLFWwindow* _window;
        const char* _name;
        uint32_t _width;
        uint32_t _height;
    };

    void on_window_resize(GLFWwindow *window, int width, int height);
}
