cmake_minimum_required(VERSION 3.7)
project(mrld_engine)
set(CMAKE_CXX_STANDARD 20)
add_executable(mrld_engine main.cpp)

# gl
find_package(OpenGL REQUIRED)

# glad
include_directories(dependencies/glad/include)
add_library(GLAD dependencies/glad/src/glad.c)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
include_directories(dependencies/glfw3/include)
add_subdirectory(dependencies/glfw3)

# mrld
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES src/window/window.cpp)
list(APPEND SOURCES src/input/mouse/mouse_handler.cpp)
list(APPEND SOURCES src/input/keyboard/keyboard_handler.cpp)
list(APPEND SOURCES src/math/vec2.cpp)
list(APPEND SOURCES src/math/vec3.cpp)
list(APPEND SOURCES src/math/vec4.cpp)
list(APPEND SOURCES src/math/mat4.cpp)
list(APPEND SOURCES src/math/quaternion.cpp)
list(APPEND SOURCES src/graphics/shader/shader.cpp)
list(APPEND SOURCES src/camera/camera.cpp)
list(APPEND SOURCES src/camera/fps_camera.cpp)
list(APPEND SOURCES src/utils/logger.cpp)
list(APPEND SOURCES src/physics/object.cpp)
list(APPEND SOURCES src/physics/physics_engine.cpp)
list(APPEND SOURCES src/physics/collisions/collision_algo.cpp)
list(APPEND SOURCES src/graphics/rendering/buffer/attrib_data_buffer.cpp)
list(APPEND SOURCES src/graphics/rendering/buffer/attrib_data_buffer.cpp)
list(APPEND SOURCES src/graphics/rendering/buffer/index_buffer.cpp)
list(APPEND SOURCES src/graphics/rendering/buffer/vertex_array.cpp)
list(APPEND SOURCES src/graphics/rendering/renderable/drawable/sprite.cpp)
list(APPEND SOURCES src/graphics/rendering/renderable/drawable/model.cpp)
list(APPEND SOURCES src/graphics/rendering/renderer/renderer.cpp)
list(APPEND SOURCES src/graphics/rendering/renderer/renderer2d.cpp)
list(APPEND SOURCES src/graphics/rendering/renderer/renderer3d.cpp)
list(APPEND SOURCES src/graphics/rendering/layer/layer.cpp)
list(APPEND SOURCES src/graphics/rendering/renderable/group/group.cpp)
list(APPEND SOURCES src/graphics/texture/texture.cpp)
list(APPEND SOURCES src/utils/timer.cpp)
list(APPEND SOURCES src/utils/file_handler.cpp)
add_library(mrld ${SOURCES})

# linking
IF (WIN32)
    target_link_libraries(mrld_engine mrld GLAD glfw opengl32)
ELSE ()
    target_link_libraries(mrld_engine mrld GLAD glfw OpenGL)
ENDIF ()