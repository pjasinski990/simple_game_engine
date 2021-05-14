#ifndef MRLD_ENGINE_WINDOW_H
#define MRLD_ENGINE_WINDOW_H

#include <exception>
class GLFWwindow;

namespace mrld {
    class Window {
    public:
        Window(const char* name, int width, int height);
        ~Window();
        void update();
        bool should_close() const;
        inline int get_width() const {return _width;}
        inline int get_height() const {return _height;}

    private:
        GLFWwindow* _window;
        const char* _name;
        int _width;
        int _height;
    };

    class WindowCreationException: public std::exception {
    public:
        explicit WindowCreationException(const char* msg): std::exception(msg) {}
        const char *what() const override;
    };

    void on_window_resize(GLFWwindow *window, int width, int height);
}

#endif //MRLD_ENGINE_WINDOW_H
