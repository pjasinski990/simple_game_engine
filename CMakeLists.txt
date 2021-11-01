cmake_minimum_required(VERSION 3.7)
project(mrld_engine)
set(CMAKE_CXX_STANDARD 20)
add_executable(mrld_engine main.cpp)

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

set(SOURCES ${PROJECT_SOURCE_DIR}/src/window/window.cpp)
list(APPEND SOURCES src/input/mouse/mouse_handler.cpp)
list(APPEND SOURCES src/input/keyboard/keyboard_handler.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/vec2.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/vec3.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/vec4.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/mat4.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/quaternion.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/shader/shader.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/camera/camera.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/utils/logger.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/rendering/buffer/attrib_data_buffer.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/rendering/buffer/index_buffer.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/rendering/buffer/vertex_array.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/rendering/renderer/renderer2d/renderable2d.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/rendering/renderer/renderer2d/renderer2d.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/rendering/layer/layer.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/rendering/layer/layer2d/layer2d.cpp)

add_library(mrld ${SOURCES})

# linking
target_link_libraries(mrld_engine mrld GLAD glfw)
