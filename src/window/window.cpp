#include <window/window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

mrld::Window::Window(const char *name, int width, int height): _window{nullptr}, _name{name}, _width{width}, _height{height}
{
    if (glfwInit() == GLFW_FALSE) {
        throw WindowCreationException("Error: initializing GLFW: glfwInit returned false");
    }
    _window = glfwCreateWindow(_width, _height, _name, nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        throw WindowCreationException("Error: creating window: glfwCreateWindow returned null");
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGL()) {
        glfwTerminate();
        throw WindowCreationException("Error: initializing GLAD: gladLoadGL returned null");
    }

    glfwSetWindowSizeCallback(_window, on_window_resize);
}

void mrld::Window::update()
{
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(_window);
}

mrld::Window::~Window()
{
    glfwTerminate();
}

bool mrld::Window::should_close() const
{
    return glfwWindowShouldClose(_window);
}

void mrld::on_window_resize(GLFWwindow *window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}


const char *mrld::WindowCreationException::what() const
{
    return exception::what();
}
