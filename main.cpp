#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <window/window.h>
#include <graphics/shader.h>
#include <input/keyboard_handler.h>
#include <input/mouse_handler.h>

int main() {
    mrld::Window w("Hello world!", 800, 600);
    mrld::KeyboardHandler handler({mrld::W, mrld::S, mrld::A, mrld::D});
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    try {
        mrld::Shader s("../sample_vertex.shader", "../sample_fragment.shader");
        s.create_shader_program();
        s.use();
    } catch (mrld::ShaderException &e) {
        std::cout << e.what() << std::endl;
    }

    while (!w.should_close()) {
        w.update();
    }
    return 0;
}
