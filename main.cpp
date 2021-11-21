#include <thread>
#include <chrono>
#include <glad/glad.h>
#include "mrld/mrld.h"

int main(void)
{
//    mrld::Logger::set_log_level(mrld::LogLevel::DBG);
    mrld::Window window("Hello test", 800, 600);
    mrld::KeyboardHandler handler({mrld::W, mrld::S, mrld::A, mrld::D, mrld::LEFT, mrld::RIGHT, mrld::SPACE, mrld::LEFT_SHIFT, mrld::ESCAPE});
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    mrld::Shader s(
            "../src/graphics/shader/shader_files/sample_vertex.shader",
            "../src/graphics/shader/shader_files/sample_fragment.shader"
    );
    s.create_shader_program();

    mrld::FPSCamera cam(
            &window,
            mrld::vec3(0.0f, 0.0f, 20.0f),
            mrld::vec3(0.0f, 0.0f, 0.0f),
            mrld::vec3(0.0f, 1.0f, 0.0f),
            4.0f/3.0f,
            1.0f,
            100.0f,
            45.0f
            );

    mrld::Texture jake_t("../res/jake.png", true);
    mrld::Texture container_t("../res/container.jpg", false);
    mrld::Layer2D layer(&s, &cam);
    mrld::Sprite *jake = new mrld::Sprite(mrld::vec3(-4, -3, 5.0f), mrld::vec2(8, 6), &jake_t);
    mrld::Sprite *container = new mrld::Sprite(mrld::vec3(-4, -3, 0.0f), mrld::vec2(8, 6), &container_t);
    layer.add(container);
    layer.add(jake);

    uint16_t fps = 0;
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    mrld::Timer timer;
    timer.reset();

    while (!window.should_close()) {
        s.use(); // shader start
        cam.update();

        window.clear();
        layer.draw();
        window.update();
        s.disable(); // shader stop

        if (handler.is_key_down(mrld::KeyCode::W)) {
            cam.go_forward();
        }
        else if (handler.is_key_down(mrld::KeyCode::S)) {
            cam.go_backward();
        }
        else if (handler.is_key_down(mrld::KeyCode::A)) {
            cam.go_left();
        }
        else if (handler.is_key_down(mrld::KeyCode::D)) {
            cam.go_right();
        }
        else if (handler.is_key_down(mrld::KeyCode::SPACE)) {
            cam.go_up();
        }
        else if (handler.is_key_down(mrld::KeyCode::LEFT_SHIFT)) {
            cam.go_down();
        }
        else if (handler.is_key_down(mrld::KeyCode::ESCAPE)) {
            cam.toggle_cursor_enabled();
            handler.debounce(mrld::KeyCode::ESCAPE);
        }

        if (timer.get_elapsed_millis() > 1000) {
            std::cout << fps << " fps" << std::endl;
            timer.reset();
            fps = 0;
        }
        ++fps;
    }
    return 0;
}
