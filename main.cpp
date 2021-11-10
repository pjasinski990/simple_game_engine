#include <thread>

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
    mrld::Layer2D layer(&s, proj);

    mrld::Texture alpha_test("../res/3px-tile.png", true);
    mrld::Texture icon("../res/mrld_icon.png", true);
    mrld::Texture jake("../res/jake.png", true);

    auto baseGroup = new mrld::Group(mrld::mat4::translate(mrld::vec3(-8.0f, -6.0f)));
    // so, blending works correctly but only if rendered back to front and textures have different depth values.
    // TODO there is one other problem with blending though - if i moved texture outside of the baseGroup, it would not blend at all
    baseGroup->add(new mrld::Sprite(mrld::vec3(0.0f, 0.0f, 0.0f), mrld::vec2(16.0f, 12.0f), &jake));
    baseGroup->add(new mrld::Sprite(mrld::vec3(0.5f, 0.5f, 0.1f), mrld::vec2(4, 4), &icon));
    baseGroup->add(new mrld::Sprite(mrld::vec3(0.0f, 0.0f, 0.2f), mrld::vec2(16, 12), &alpha_test));
    layer.add(baseGroup);

    uint16_t fps = 0;
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    mrld::mat4 model = mrld::mat4::identity();
    mrld::Timer timer;
    timer.reset();
    while (!window.should_close()) {
        if (handler.is_key_down(mrld::KeyCode::W)) {
            model *= mrld::mat4::translate(mrld::vec3(0.0f, 0.01f));
        }
        else if (handler.is_key_down(mrld::KeyCode::S)) {
            model *= mrld::mat4::translate(mrld::vec3(0.0f, -0.01f));
        }
        else if (handler.is_key_down(mrld::KeyCode::A)) {
            model *= mrld::mat4::translate(mrld::vec3(-0.01f,0.0f));
        }
        else if (handler.is_key_down(mrld::KeyCode::D)) {
            model *= mrld::mat4::translate(mrld::vec3(0.01f, 0.0f));
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

        ++fps;
        if (timer.get_elapsed_time() >= 1000) {
            std::cout << fps << " fps" << std::endl;
            fps = 0;
            timer.reset();
        }
    }
    return 0;
}
