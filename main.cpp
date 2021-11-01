#include <ctime>

#include <glad/glad.h>

#include "mrld/mrld.h"

#define SPRITES_HORIZONTAL (80 * 3.5f)
#define SPRITES_VERTICAL (60 * 3.5f)

int main(void)
{
    mrld::Window window("Hello simulation", 800, 600);
    mrld::KeyboardHandler handler({mrld::W, mrld::S, mrld::A, mrld::D});
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    mrld::Shader s(
            "../src/graphics/shader/shader_files/sample_vertex.shader",
            "../src/graphics/shader/shader_files/sample_fragment.shader"
            );
    s.create_shader_program();

    mrld::mat4 proj = mrld::mat4::orthographic(-4, 4, -3, 3, -1, 1);
    mrld::Layer2D layer(s, proj);

    float dx = 8.0f / SPRITES_HORIZONTAL;
    float dy = 6.0f / SPRITES_VERTICAL;
    for (int i = 0; i < SPRITES_HORIZONTAL; ++i) {
        for (int j = 0; j < SPRITES_VERTICAL; ++j) {
            float r = rand() % 1000 / 1000.0f;
            layer.add(new mrld::Renderable2D(mrld::vec2(-4.0f + i * dx, -3.0f + j * dy), mrld::vec2(dx, dy), mrld::vec4(r, 0.0f, 1.0f, 0.0f)));
        }
    }

    uint16_t fps = 0;
    clock_t begin_time = clock();
    glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
    while (!window.should_close()) {
        mrld::vec2 light_pos(m_handler.get_x() / 800.0f * 4.0f - 1.5f, -m_handler.get_y() / 600.0f * 3.0f + 2.0f);
        light_pos = (light_pos - mrld::vec2(0.5f, 0.5f)) * 2.0f;
        s.set_vec2("light_position", light_pos);

        window.clear();
        layer.draw();
        window.update();

        ++fps;
        float delta = float(clock() - begin_time) /  CLOCKS_PER_SEC * 1000.0f;
        if (delta > 1000.0f) {
            std::cout << fps << " fps" << std::endl;
            fps = 0;
            begin_time = clock();
        }
    }
    return 0;
}
