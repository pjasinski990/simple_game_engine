#include <thread>
#include <chrono>
#include <glad/glad.h>

#include "mrld/mrld.h"
#include "res/cube_vertices.h"

int main(void)
{
//    mrld::Logger::set_log_level(mrld::LogLevel::DBG);
    mrld::Window window("Hello test", 800, 600);
    mrld::KeyboardHandler handler({
        mrld::KeyCode::W,
        mrld::KeyCode::S,
        mrld::KeyCode::A,
        mrld::KeyCode::D,
        mrld::KeyCode::LEFT,
        mrld::KeyCode::RIGHT,
        mrld::KeyCode::SPACE,
        mrld::KeyCode::LEFT_SHIFT,
        mrld::KeyCode::ESCAPE,
        mrld::KeyCode::KEYPAD_1,
        mrld::KeyCode::KEYPAD_2
        });
    mrld::MouseHandler m_handler({mrld::MouseButton::BUTTON_LEFT, mrld::MouseButton::BUTTON_RIGHT});

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
            500.0f,
            45.0f
            );

    mrld::Texture container_t("../res/container.jpg", false);
    mrld::Texture dirt_t("../res/dirt.png", true);

    mrld::Renderer3D r3(&s);
    mrld::Layer layer3d(&s, &r3, &cam);
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 40; ++j) {
            mrld::Model *box = new mrld::Model(mrld::cube::vertices, mrld::cube::vertex_count, mrld::cube::indices, mrld::cube::index_count, &container_t);
            box->scale(mrld::vec3(10.0f, 10.0f, 10.0f));
            box->rotate(mrld::vec3(0.0f, 0.0f, 1.0f), mrld::math_constants::pi8);
            box->translate(mrld::vec3(i * 12.0f, 3.80f, j * -12.0f));
            layer3d.add(box);
        }
    }

    mrld::VertexData floor[4] = {
            { mrld::vec3(-1000, 0, -1000),
            mrld::vec3(0, 1, 0),
            mrld::vec2(0, 0),
            -1,
            0xffa0a0a0
            },
            { mrld::vec3(-1000, 0, 1000),
                mrld::vec3(0, 1, 0),
                mrld::vec2(0, 1),
                -1,
                0xffa0a0a0
            },
            { mrld::vec3(1000, 0, 1000),
                mrld::vec3(0, 1, 0),
                mrld::vec2(1, 1),
                -1,
                0xffa0a0a0
            },
            { mrld::vec3(1000, 0, -1000),
                mrld::vec3(1, 0, 0),
                mrld::vec2(0, 1),
                -1,
                0xffa0a0a0 }
    };
    uint16_t floor_indices[] = {0, 1, 2, 2, 3, 0};
    layer3d.add(new mrld::Model(floor, 4, floor_indices, 6));

    mrld::physics_properties cube_props;
    cube_props.position = mrld::vec3();
    cube_props.velocity = mrld::vec3(0.0f, 10.0f, 0.0f);
    cube_props.acceleration = mrld::vec3();
    cube_props.mass = 1.0f;
    cube_props.bounciness = 0.0f;
    mrld::Model *cube = new mrld::Model(mrld::cube::vertices, mrld::cube::vertex_count, mrld::cube::indices, mrld::cube::index_count);
    mrld::Object *cube_o = new mrld::Object(cube, new mrld::SphereCollider(1.0f), cube_props);
    layer3d.add(cube_o->get_model());

    mrld::PhysicsEngine world;
    world.add(cube_o);

    uint16_t fps = 0;
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    mrld::Timer timer;
    timer.reset();

    while (!window.should_close()) {
        world.step(0.003f);
        window.clear();
        layer3d.draw();
        window.update();

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
        else if (handler.is_key_down(mrld::KeyCode::KEYPAD_1)) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        else if (handler.is_key_down(mrld::KeyCode::KEYPAD_2)) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
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
