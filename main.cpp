#include <ctime>

#include <glad/glad.h>

#include "mrld/mrld.h"

#define SPRITES_HORIZONTAL (80 * 3.5)
#define SPRITES_VERTICAL (60 * 3.5)

int main(void)
{
    // TODO create error retrieval system for opengl calls;
//    mrld::Logger::set_log_level(mrld::LogLevel::DBG);

#ifdef TEST
    mrld::Shader s1(
            "../src/graphics/shader/shader_files/sample_vertex.shader",
            "../src/graphics/shader/shader_files/sample_fragment.shader"
    );
    s1.create_shader_program();
    mrld::mat4 proj1 = mrld::mat4::orthographic(-4, 4, -3, 3, -1, 1);
    mrld::Layer2D layer1(s1, proj1);
    float dx = 8.0f / SPRITES_HORIZONTAL;
    float dy = 6.0f / SPRITES_VERTICAL;
    for (int i = 0; i < SPRITES_HORIZONTAL; ++i) {
        for (int j = 0; j < SPRITES_VERTICAL; ++j) {
            float g = rand() % 1000 / 1000.0f;
            layer1.add(new mrld::Sprite(mrld::vec3(-4.0f + i * dx, -3.0f + j * dy), mrld::vec2(dx, dy), mrld::vec4(0.0f, g, 1.0f, 0.0f)));
        }
    }
#endif

    mrld::Window window("Hello simulation", 800, 600);
    mrld::KeyboardHandler handler({mrld::W, mrld::S, mrld::A, mrld::D});
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    mrld::Shader s(
            "../src/graphics/shader/shader_files/sample_vertex.shader",
            "../src/graphics/shader/shader_files/sample_fragment.shader"
    );
    s.create_shader_program();
    mrld::mat4 proj = mrld::mat4::orthographic(-8, 8, -6, 6, -1, 1);
    mrld::Layer2D layer(s, proj);

//    mrld::Texture tex1("../jake.png", 0, true);
//    s.set_int("tex", 0);
//    tex1.bind(0);

    mrld::Texture tex2("../container.jpg", 0, false);
    s.set_int("tex", 2);
    tex2.bind(0);

    auto baseGroup = new mrld::Group2D(mrld::mat4::translate(mrld::vec3(-8.0f, -6.0f)));
    float ratio = 1.0f;
    baseGroup->add(new mrld::Sprite(mrld::vec3(6.0f, 4.0f), mrld::vec2(8.0f * ratio, 6.0f), mrld::vec4(0.8f, 0.5f, 0.9f, 0.0f)));

    baseGroup->add(new mrld::Sprite(mrld::vec3(0.0f, 5.0f), mrld::vec2(5.0f * ratio, 5.0f), mrld::color::WHITE, 0, 1));
    baseGroup->add(new mrld::Sprite(mrld::vec3(1.0f, 1.0f), mrld::vec2(2.0 * ratio, 2.0f), mrld::vec4(1.0f)));
    auto secGroup = new mrld::Group2D(mrld::mat4::translate(mrld::vec3(5.0f, 1.0f)));
    secGroup->add(new mrld::Sprite(mrld::vec3(), mrld::vec2(2.0f * ratio, 2.0f), mrld::vec4(0.0f, 1.0f)));
    baseGroup->add(secGroup);
    auto thGroup = new mrld::Group2D(mrld::mat4::translate(mrld::vec3(9.0f, 1.0f)));
    thGroup->add(new mrld::Sprite(mrld::vec3(), mrld::vec2(2.0f * ratio, 2.0f), mrld::vec4(0.0f, 0.0f, 1.0f)));
    baseGroup->add(thGroup);
    layer.add(baseGroup);

    uint16_t fps = 0;
    clock_t begin_time = clock();
    glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
    while (!window.should_close()) {
#if TEST
        s1.use();
        mrld::vec2 light_pos(m_handler.get_x() / 800.0f * 4.0f - 1.5f, -m_handler.get_y() / 600.0f * 3.0f + 2.0f);
        light_pos = (light_pos - mrld::vec2(0.5f, 0.5f)) * 2.0f;
        s1.set_vec2("light_position", light_pos);
        window.clear();
        layer1.draw();
        window.update();
#else
        mrld::vec2 light_pos(m_handler.get_x() / 800.0f * 16.0f - 8.0f, -m_handler.get_y() / 600.0f * 12.0f + 6.0f);
        s.use();
        s.set_vec2("light_position", light_pos);
        s.remove();

        window.clear();
        layer.draw();
        window.update();
#endif
        // TODO implement timer class
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
