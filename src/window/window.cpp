#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "../utils/logger.h"

namespace mrld
{
    Window::Window(const char *name, uint16_t width, uint16_t height) :
    _window{nullptr},
    _name{name},
    _width{width},
    _height{height}
    {
        if (glfwInit() == GLFW_FALSE) {
            Logger::log(LogLevel::WRN, "%s", "While initializing GLFW: glfwInit returned false");
            throw std::runtime_error("Error initializing GLFW");
        }
        _window = glfwCreateWindow(_width, _height, _name, nullptr, nullptr);
        if (!_window) {
            glfwTerminate();
            Logger::log(LogLevel::WRN, "%s", "While initializing GLFW: glfwCreateWindow returned null");
            throw std::runtime_error("Error initializing GLFW");
        }
        glfwMakeContextCurrent(_window);

        if (!gladLoadGL()) {
            glfwTerminate();
            Logger::log(LogLevel::WRN, "%s", "While initializing GLAD: gladLoadGL returned null");
            throw std::runtime_error("Error initializing GLAD");
        }

        glfwSetWindowSizeCallback(_window, on_window_resize);
        glfwSwapInterval(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Window::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::update() const
    {
        glfwPollEvents();
        glfwSwapBuffers(_window);
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    bool Window::should_close() const
    {
        return glfwWindowShouldClose(_window);
    }

    void on_window_resize(GLFWwindow *window, int width, int height)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }
}
