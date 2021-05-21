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

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    float vertices2[] = {
            1.0f, 1.0f, 0.0f,
            5.0f, 1.0f, 0.0f,
            3.0f, 3.0f, 0.0f
    };

    try {
        mrld::Shader s("../sample_vertex.shader", "../sample_fragment.shader");
        s.create_shader_program();
        s.use();

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        mrld::mat4 proj = mrld::mat4::orthographic(0, 6, 0, 4, -1, 1);
        s.set_mat4("proj_matrix", proj);

    } catch (mrld::ShaderException &e) {
        std::cout << e.what() << std::endl;
    }

    while (!w.should_close()) {
        w.clear();
        glClearColor(0.2, 0.5, 0.3, 0.0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        w.update();
    }
    return 0;
}
