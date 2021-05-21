#ifndef MRLD_ENGINE_WINDOW_H
#define MRLD_ENGINE_WINDOW_H

#include <stdexcept>

class GLFWwindow;

namespace mrld {
    class Window {
    public:
        Window(const char* name, int width, int height);
        ~Window();
        void clear() const;
        void update() const;
        bool should_close() const;
        inline int get_width() const {return _width;}
        inline int get_height() const {return _height;}

    private:
        GLFWwindow* _window;
        const char* _name;
        int _width;
        int _height;
    };

    // TODO exchange exceptions for logging errors maybe
    class WindowCreationException: public std::runtime_error {
    public:
        explicit WindowCreationException(const char* msg): std::runtime_error(msg) {}
        virtual ~WindowCreationException() = default;
        virtual const char *what() const noexcept override { return runtime_error::what(); }
    };

    void on_window_resize(GLFWwindow *window, int width, int height);
}

#endif //MRLD_ENGINE_WINDOW_H
