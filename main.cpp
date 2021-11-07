#include <ctime>
#include <glad/glad.h>
#include "mrld/mrld.h"

int main(void)
{
//    mrld::Logger::set_log_level(mrld::LogLevel::DBG);
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

    mrld::Texture tex1("../jake.png", true);
    mrld::Texture tex2("../container.jpg");

    auto baseGroup = new mrld::Group(mrld::mat4::translate(mrld::vec3(-8.0f, -6.0f)));
    float ratio = 1.3f;
    mrld::vec3 position(6.0f, 4.0f, 0.0f);
    mrld::vec2 size(8.0f * ratio, 6.0f);
    baseGroup->add(new mrld::Sprite(position + mrld::vec3(0.0f, -2.0f), mrld::vec2(2.0f, 2.0f), mrld::color::WHITE, 0, &tex1));
    baseGroup->add(new mrld::Sprite(position, size, mrld::color::BLACK, 0, &tex2));
    layer.add(baseGroup);

    uint16_t fps = 0;
    clock_t begin_time = clock();
    glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
    while (!window.should_close()) {
        mrld::vec2 light_pos(m_handler.get_x() / 800.0f * 16.0f - 8.0f, -m_handler.get_y() / 600.0f * 12.0f + 6.0f);
        s.use();
        s.set_vec2("light_position", light_pos);
        s.disable();

        window.clear();
        layer.draw();
        window.update();

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
