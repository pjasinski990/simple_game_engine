cmake_minimum_required(VERSION 3.7)
project(mrld_engine)
set(CMAKE_CXX_STANDARD 14)

# dependencies
include_directories(dependencies/glad/include)
add_library(GLAD dependencies/glad/src/glad.c)

include_directories(dependencies/glfw3/include)
add_subdirectory(dependencies/glfw3)

# libraries
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES ${PROJECT_SOURCE_DIR}/src/window/window.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/input/mouse_handler.cpp)
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/input/keyboard_handler.cpp)


add_library(mrld ${SOURCES})

# linking
add_executable(mrld_engine main.cpp)
target_link_libraries(mrld_engine GLAD glfw mrld)
