#include <thread>
#include <chrono>

#include "mrld/mrld.h"
#include "res/cube_vertices.h"

void handle_keys(mrld::KeyboardHandler& handler, mrld::FPSCamera &cam, float dt);

int main(void)
{
    mrld::Window window("Hello test", 800, 600);

    mrld::MouseHandler m_handler({mrld::MouseButton::BUTTON_LEFT, mrld::MouseButton::BUTTON_RIGHT});
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
        mrld::KeyCode::KEYPAD_2,
        mrld::KeyCode::KEYPAD_3
        });

    mrld::Shader s( "../src/graphics/shader/shader_files/sample_vertex.shader",
                  "../src/graphics/shader/shader_files/sample_fragment.shader" );
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

    mrld::Renderer3D r3(&s);
    mrld::Layer layer3d(&s, &r3, &cam);

    mrld::PhysicsEngine world;
    world.add_solver(new mrld::SimplePositionCorrectionSolver());
    world.add_solver(new mrld::ImpulseSolver());

    // FLOOR
    mrld::VertexData floor[4] = {
            { mrld::vec3(-1000, 0, -1000), mrld::vec3(0, 1, 0), mrld::vec2(0, 0), -1, -1, 0xffa0a0a0 },
            { mrld::vec3(-1000, 0, 1000), mrld::vec3(0, 1, 0), mrld::vec2(0, 1000), -1, -1,  0xffa0a0a0 },
            { mrld::vec3(1000, 0, 1000), mrld::vec3(0, 1, 0), mrld::vec2(1000, 1000), -1, -1,  0xffa0a0a0 },
            { mrld::vec3(1000, 0, -1000), mrld::vec3(1, 0, 0), mrld::vec2(0, 1000), -1, -1,  0xffa0a0a0 } };
    uint16_t floor_indices[] = {0, 1, 2, 2, 3, 0};
    mrld::Model *floor_model = new mrld::Model(floor, 4, floor_indices, 6);
    mrld::Body *floor_o = new mrld::Body(floor_model, new mrld::PlaneCollider(mrld::vec3(0.0f, 1.0f, 0.0f), 0.0f), mrld::physics_properties());
    floor_o->phys_properties.mass_inv = 0.0f;
    floor_o->t.position = mrld::vec3(0.0f, -3.0f, 0.0f);
    floor_o->update_model();
    layer3d.add(floor_o->get_model());
    world.add(floor_o);

    // CUBES
    mrld::Texture container_t("../res/container.jpg", false);
    mrld::physics_properties cube_props;
    cube_props.velocity = mrld::vec3(0.0f, 0.0f, 0.0f);
    cube_props.bounciness = 0.6f;
    float dist = 10.0f;

    mrld::material cube_material;
    cube_material.specular = mrld::vec3(1.0f, 1.0f, 1.0f);
    cube_material.diffuse = mrld::vec3(1.0f, 1.0f, 1.0f);
    cube_material.ambient = mrld::vec3(0.8f, 0.8f, 0.6f);
    cube_material.specular_e = 32.0f;
    cube_material.dissolve = 1.0f;
    for (int i = 0; i < 20; ++i) {
        mrld::Model *cube = new mrld::Model(mrld::cube::vertices, mrld::cube::vertex_count, mrld::cube::indices, mrld::cube::index_count, &container_t);
        cube->assign_material(cube_material);
        mrld::Body *cube_o = new mrld::RigidBody(cube, new mrld::SphereCollider(mrld::vec3(0.5f, 0.5f, 0.5f), 1.0f), cube_props);
        const float rand_x = static_cast<float>(rand()) / RAND_MAX * dist - dist / 2.0f;
        const float rand_y = static_cast<float>(rand()) / RAND_MAX * dist;
        const float rand_z = static_cast<float>(rand()) / RAND_MAX * dist - dist / 2.0f;
        cube_o->t.position = mrld::vec3(rand_x, rand_y, rand_z);
        cube_o->t.rotation = mrld::quat(mrld::vec3(0.0f, 1.0f, 0.0f), 5.0f * rand() / RAND_MAX);
        layer3d.add(cube_o->get_model());
        world.add(cube_o);
    }

    cube_material.specular_e = 128.0f;
    floor_model->assign_material(cube_material);

    mrld::Model *tree = mrld::ObjModelParser::parse_obj_to_model("../res/tree1.obj");
    std::vector<mrld::material> tree_mat = mrld::ObjModelParser::parse_mtl_to_materials("../res/tree1.mtl");
    tree->set_materials(tree_mat);
    tree->translate(mrld::vec3(-10.0f, -3.0f, -20.0f));
    layer3d.add(tree);

    mrld::Model *tree2 = mrld::ObjModelParser::parse_obj_to_model("../res/tree2.obj");
    std::vector<mrld::material> tree2_mat = mrld::ObjModelParser::parse_mtl_to_materials("../res/tree2.mtl");
    tree2->set_materials(tree2_mat);
    tree2->translate(mrld::vec3(0.0f, -3.0f, -20.0f));
    layer3d.add(tree2);

    mrld::Model *tree3 = mrld::ObjModelParser::parse_obj_to_model("../res/tree3.obj");
    std::vector<mrld::material> tree3_mat = mrld::ObjModelParser::parse_mtl_to_materials("../res/tree3.mtl");
    tree3->set_materials(tree3_mat);
    tree3->translate(mrld::vec3(10.0f, -3.0f, -20.0f));
    layer3d.add(tree3);

    mrld::directional_light light;
    light.direction = mrld::vec3(1.0f, -1.0f, -1.0f);
    light.diffuse = mrld::vec3(1.0f, 1.0f, 1.0f) * 0.7f;
    light.specular = mrld::vec3(1.0f, 1.0f, 1.0f) * 0.7f;
    light.ambient = mrld::vec3(0.1f, 0.1f, 0.1f) * 0.7f;
    s.set_directional_light(light);

    mrld::point_light p_light;
    p_light.position = mrld::vec3(20.0f, 5.0f, 0.0f);
    p_light.diffuse = mrld::vec3(1.0f, 1.0f, 1.0f);
    p_light.specular = mrld::vec3(1.0f, 1.0f, 1.0f);
    p_light.ambient = mrld::vec3(0.2f, 0.2f, 0.2f);
    p_light.constant = 1.0f;
    p_light.linear = 0.07f;
    p_light.quadratic = 0.002f;
    layer3d.add_point_light(p_light);

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    mrld::Timer timer;
    timer.reset();

    uint64_t dt = 1000000u / 64u;    // 64 tick rate
    float dtf = dt * 0.000001f;
    uint64_t accumulator = 0u;
    uint64_t current_time = timer.get_elapsed_micros();
    uint16_t fps = 0;
    uint64_t fps_timer = 0u;

    while (!window.should_close()) {
        uint64_t new_time = timer.get_elapsed_micros();
        uint64_t frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        while (accumulator > dt) {
            world.step(dtf);
            accumulator -= dt;

            // leaving in next iteration
            if (accumulator < dt) {
                world.update_models();
            }
        }
        world.interpolate_previous_state(static_cast<float>(accumulator)/ static_cast<float>(dt));

        handle_keys(handler, cam, frame_time * 0.000001);
        window.clear();
        layer3d.draw();
        window.update();

        if (timer.get_elapsed_millis() - fps_timer > 1000u) {
            std::cout << fps << " fps" << std::endl;
            fps_timer = timer.get_elapsed_millis();
            fps = 0;
        }
        ++fps;
    }
    return 0;
}

void handle_keys(mrld::KeyboardHandler& handler, mrld::FPSCamera &cam, float dt)
{
    if (handler.is_key_down(mrld::KeyCode::W)) {
        cam.go_forward(dt);
    }
    else if (handler.is_key_down(mrld::KeyCode::S)) {
        cam.go_backward(dt);
    }
    else if (handler.is_key_down(mrld::KeyCode::A)) {
        cam.go_left(dt);
    }
    else if (handler.is_key_down(mrld::KeyCode::D)) {
        cam.go_right(dt);
    }
    else if (handler.is_key_down(mrld::KeyCode::SPACE)) {
        cam.go_up(dt);
    }
    else if (handler.is_key_down(mrld::KeyCode::LEFT_SHIFT)) {
        cam.go_down(dt);
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
}
