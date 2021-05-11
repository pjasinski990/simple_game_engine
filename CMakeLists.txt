cmake_minimum_required(VERSION 3.7)
project(mrld_engine)
set(CMAKE_CXX_STANDARD 14)

include_directories(dependencies/glad/include)
add_library(GLAD dependencies/glad/src/glad.c)

include_directories(dependencies/glfw3/include)
add_subdirectory(dependencies/glfw3)


add_executable(mrld_engine main.cpp)
target_link_libraries(mrld_engine GLAD glfw)
