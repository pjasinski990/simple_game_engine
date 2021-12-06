#pragma once
#define GLFW_INCLUDE_NONE

// Math
#include "../../src/math/math_util.h"
#include "../../src/math/quaternion.h"
#include "../../src/math/mat4.h"
#include "../../src/math/vec2.h"
#include "../../src/math/vec3.h"
#include "../../src/math/vec4.h"

// Camera
#include "../../src/camera/camera.h"
#include "../../src/camera/fps_camera.h"

// Graphics misc
#include "../../src/graphics/rendering/buffer/attrib_data_buffer.h"
#include "../../src/graphics/rendering/buffer/index_buffer.h"
#include "../../src/graphics/rendering/buffer/vertex_array.h"
#include "../../src/graphics/rendering/buffer/vertex_data.h"
#include "../../src/graphics/color.h"

// Graphics rendering
#include "../../src/graphics/rendering/renderable/renderable.h"
#include "../../src/graphics/rendering/renderable/drawable/drawable.h"
#include "../../src/graphics/rendering/renderable/drawable/sprite.h"
#include "../../src/graphics/rendering/renderable/drawable/model.h"
#include "../../src/graphics/rendering/renderer/renderer.h"
#include "../../src/graphics/rendering/renderer/renderer2d.h"
#include "../../src/graphics/rendering/renderer/renderer3d.h"
#include "../../src/graphics/rendering/layer/layer.h"
#include "../../src/graphics/texture/texture.h"
#include "../../src/graphics/shader/shader.h"

// Physics
#include "../../src/physics/transform.h"
#include "../../src/physics/body.h"
#include "../../src/physics/rigidbody.h"
#include "../../src/physics/physics_engine.h"
#include "../../src/physics/physics_properties.h"
#include "../../src/physics/collisions/collision_algo.h"
#include "../../src/physics/collisions/collision_point.h"
#include "../../src/physics/collisions/collision.h"
#include "../../src/physics/collisions/collider.h"
#include "../../src/physics/collisions/colliders/sphere_collider.h"
#include "../../src/physics/collisions/colliders/plane_collider.h"
#include "../../src/physics/collisions/solver/solver.h"
#include "../../src/physics/collisions/solver/impulse_solver.h"
#include "../../src/physics/collisions/solver/recursive_position_correction_solver.h"
#include "../../src/physics/collisions/solver/simple_position_correction_solver.h"

// IO
#include "../../src/input/key_code.h"
#include "../../src/input/keyboard/keyboard_handler.h"
#include "../../src/input/mouse/mouse_handler.h"

// Utils
#include "../../src/utils/logger.h"
#include "../../src/utils/debug.h"
#include "../../src/utils/timer.h"
#include "../../src/utils/obj_model_parser.h"

// Window
#include "../../src/window/window.h"
