#include <thread>

#include <glad/glad.h>
#include "mrld/mrld.h"

void handle_input();

int main(void)
{
//    mrld::Logger::set_log_level(mrld::LogLevel::DBG);
    mrld::Window window("Hello simulation", 800, 600);
    mrld::KeyboardHandler handler({mrld::W, mrld::S, mrld::A, mrld::D, mrld::LEFT, mrld::RIGHT, mrld::SPACE, mrld::LEFT_SHIFT});
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    mrld::Shader s(
            "../src/graphics/shader/shader_files/sample_vertex.shader",
            "../src/graphics/shader/shader_files/sample_fragment.shader"
    );
    s.create_shader_program();

    // MVP matrices
    mrld::Camera cam(
            mrld::vec3(10.0f, 10.0f, -20.0f),
            mrld::vec3(0.0f, 0.0f, 0.0f),
            mrld::vec3(0.0f, 1.0f, 0.0f),
            4.0f/3.0f,
            1.0f,
            100.0f,
            45.0f
            );

    mrld::mat4 model = mrld::mat4::identity();
    mrld::mat4 view = mrld::mat4::identity();
    view = cam.get_view();
    mrld::mat4 proj = cam.get_proj();

    mrld::Texture jake("../res/jake.png", true);
    mrld::Renderer2D r(&s);
    mrld::Sprite *test = new mrld::Sprite(mrld::vec3(-4, -3, 0.00), mrld::vec2(8, 6), &jake);

    uint16_t fps = 0;
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    mrld::Timer timer;
    timer.reset();

    while (!window.should_close()) {
        s.use(); // shader start
        cam.update();
        view = cam.get_view();
        s.set_mat4("view_matrix", view);
        s.set_mat4("projection_matrix", proj);

        window.clear();
        r.begin();
        r.submit(*test);
        r.end();
        r.flush();
        window.update();
        s.disable(); // shader stop

        ++fps;
        if (timer.get_elapsed_time() >= 1000) {
            std::cout << fps << " fps" << std::endl;
            fps = 0;
            timer.reset();
        }

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

        if (handler.is_key_down(mrld::KeyCode::LEFT)) {
            model *= mrld::mat4::rotate_z(0.002f);
        }
        else if (handler.is_key_down(mrld::KeyCode::RIGHT)) {
            model *= mrld::mat4::rotate_z(-0.002f);
        }
    }
    return 0;
}
