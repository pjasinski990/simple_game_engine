#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <window/window.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <input/keyboard_handler.h>
#include <input/mouse_handler.h>

int main() {
    float vertices[] = {
            -0.5f, -0.5f, 1.0f,
            0.5f, -0.5f, 1.0f,
            0.0f,  0.5f, 1.0f
    };

    mrld::Window w("Hello world!", 800, 600);
    std::vector<mrld::KeyCode> keys = {mrld::W, mrld::S, mrld::A, mrld::D};

    mrld::KeyboardHandler handler(keys);
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    while (!w.should_close()) {
        w.update();
    }
    return 0;
}
