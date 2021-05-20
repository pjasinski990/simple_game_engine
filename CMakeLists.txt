cmake_minimum_required(VERSION 3.7)
project(mrld_engine)
set(CMAKE_CXX_STANDARD 14)

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
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/input/mouse_handler.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/input/keyboard_handler.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/vec2.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/vec3.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/vec4.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/mat4.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/math/quaternion.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/graphics/shader.cpp)

add_library(mrld ${SOURCES})



# linking
add_executable(mrld_engine main.cpp)
target_link_libraries(mrld_engine mrld GLAD glfw)
