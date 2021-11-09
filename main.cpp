#include <ctime>
#include <glad/glad.h>
#include "mrld/mrld.h"

int main(void)
{
//    mrld::Logger::set_log_level(mrld::LogLevel::DBG);
    mrld::Window window("Hello simulation", 800, 600);
    mrld::KeyboardHandler handler({mrld::W, mrld::S, mrld::A, mrld::D, mrld::LEFT, mrld::RIGHT});
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
    mrld::vec2 size(8.0f, 6.0f / ratio);
    baseGroup->add(new mrld::Sprite(mrld::vec3(9.0f, 3.2f, 0), size, mrld::color::RED, 0));
    baseGroup->add(new mrld::Sprite(mrld::vec3(8.0f, 0, 0), size, mrld::color::BLACK, 0, &tex2));
    layer.add(baseGroup);

    uint16_t fps = 0;
    clock_t begin_time = clock();
    glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
    mrld::mat4 model = mrld::mat4::identity();
    while (!window.should_close()) {
        if (handler.is_key_down(mrld::KeyCode::W)) {
            model *= mrld::mat4::translate(mrld::vec3(0.0f, 0.01f));
        }
        else if (handler.is_key_down(mrld::KeyCode::S)) {
            model *= mrld::mat4::translate(mrld::vec3(0.0f, -0.01));
        }
        else if (handler.is_key_down(mrld::KeyCode::A)) {
            model *= mrld::mat4::translate(mrld::vec3(-0.01,0.0f));
        }
        else if (handler.is_key_down(mrld::KeyCode::D)) {
            model *= mrld::mat4::translate(mrld::vec3(0.01, 0.0f));
        }
        if (handler.is_key_down(mrld::KeyCode::LEFT)) {
            model *= mrld::mat4::rotate_z(0.002f);
        }
        else if (handler.is_key_down(mrld::KeyCode::RIGHT)) {
            model *= mrld::mat4::rotate_z(-0.002f);
        }

        s.use();
        s.set_mat4("model_matrix", model);
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
