#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <window/window.h>
#include <graphics/shader.h>
#include <input/keyboard_handler.h>
#include <input/mouse_handler.h>
#include <math/constants.h>

int main() {
    mrld::Window w("Hello world!", 800, 600);
    mrld::KeyboardHandler handler({mrld::W, mrld::S, mrld::A, mrld::D});
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
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

        mrld::mat4 proj = mrld::mat4::orthographic(-1, 1, -1, 1, -1, 1);
        mrld::mat4 model = mrld::mat4::identity();

        mrld::mat4 tr = mrld::mat4::translate(mrld::vec3(0.0f, 0.8f, 0.0f));
        mrld::mat4 rotz = mrld::mat4::rotate_z(mrld::constants::pi * 45.0f / 180.0f);
        mrld::mat4 rotx = mrld::mat4::rotate_x(mrld::constants::pi * 80.0f / 180.0f);
        model = model * tr * rotz * rotx;

        s.set_mat4("proj_matrix", proj);
        s.set_mat4("model_matrix", model);

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
