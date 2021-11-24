#pragma once

#include "../src/graphics/rendering/buffer/vertex_data.h"

namespace mrld
{
    VertexData cube_vertices[] {
            // front face
            {
                    vec3(0.0f, 0.0f, 1.0f),   // position
                    vec3(0.0f, 0.0f, 1.0f),   // normal
                    vec2(0.0f, 0.0f),    // tex coords
                    -1.0f,  // tex slot
                    0xffff0000  // color - blue
            },
            {
                    vec3(1.0f, 0.0f, 1.0f),
                    vec3(0.0f, 0.0f, 1.0f),
                    vec2(1.0f, 0.0f),
                    -1.0f,
                    0xffff0000
            },
            {
                    vec3(1.0f, 1.0f, 1.0f),
                    vec3(0.0f, 0.0f, -1.0f),
                    vec2(1.0f, 1.0f),
                    -1.0f,
                    0xffff0000
            },
            {
                    vec3(0.0f, 1.0f, 1.0f),
                    vec3(0.0f, 0.0f, 1.0f),
                    vec2(0.0f, 1.0f),
                    -1.0f,
                    0xffff0000
            },
            // back face
            {
                    vec3(0.0f, 0.0f, 0.0f),   // position
                    vec3(0.0f, 0.0f, -1.0f),   // normal
                    vec2(0.0f, 0.0f),    // tex coords
                    -1.0f,  // tex slot
                    0xffff0000  // color - blue
            },
            {
                    vec3(0.0f, 1.0f, 0.0f),
                    vec3(0.0f, 0.0f, -1.0f),
                    vec2(0.0f, 1.0f),
                    -1.0f,
                    0xffff0000
            },
            {
                    vec3(1.0f, 1.0f, 0.0f),
                    vec3(0.0f, 0.0f, -1.0f),
                    vec2(1.0f, 1.0f),
                    -1.0f,
                    0xffff0000
            },
            {
                    vec3(1.0f, 0.0f, 0.0f),
                    vec3(0.0f, 0.0f, -1.0f),
                    vec2(1.0f, 0.0f),
                    -1.0f,
                    0xffff0000
            },
            // left face
            {
                    vec3(0.0f, 0.0f, 0.0f),   // position
                    vec3(-1.0f, 0.0f, 0.0f),   // normal
                    vec2(0.0f, 0.0f),    // tex coords
                    -1.0f,  // tex slot
                    0xff0000ff  // color - red
            },
            {
                    vec3(0.0f, 0.0f, 1.0f),
                    vec3(-1.0f, 0.0f, 0.0f),
                    vec2(1.0f, 0.0f),
                    -1.0f,
                    0xff0000ff
            },
            {
                    vec3(0.0f, 1.0f, 1.0f),
                    vec3(-1.0f, 0.0f, 0.0f),
                    vec2(1.0f, 1.0f),
                    -1.0f,
                    0xff0000ff
            },
            {
                    vec3(0.0f, 1.0f, 0.0f),
                    vec3(-1.0f, 0.0f, 0.0f),
                    vec2(0.0f, 1.0f),
                    -1.0f,
                    0xff0000ff
            },
            // right face
            {
                    vec3(1.0f, 0.0f, 1.0f),   // position
                    vec3(1.0f, 0.0f, 0.0f),   // normal
                    vec2(0.0f, 0.0f),    // tex coords
                    -1.0f,  // tex slot
                    0xff0000ff  // color - red
            },
            {
                    vec3(1.0f, 0.0f, 0.0f),
                    vec3(1.0f, 0.0f, 0.0f),
                    vec2(1.0f, 0.0f),
                    -1.0f,
                    0xff0000ff
            },
            {
                    vec3(1.0f, 1.0f, 0.0f),
                    vec3(1.0f, 0.0f, 0.0f),
                    vec2(1.0f, 1.0f),
                    -1.0f,
                    0xff0000ff
            },
            {
                    vec3(1.0f, 1.0f, 1.0f),
                    vec3(1.0f, 0.0f, 0.0f),
                    vec2(0.0f, 1.0f),
                    -1.0f,
                    0xff0000ff
            },
            // top face
            {
                    vec3(0.0f, 1.0f, 0.0f),   // position
                    vec3(0.0f, 1.0f, 0.0f),   // normal
                    vec2(0.0f, 0.0f),    // tex coords
                    -1.0f,  // tex slot
                    0xff00ff00  // color - green
            },
            {
                    vec3(0.0f, 1.0f, 1.0f),
                    vec3(0.0f, 1.0f, 0.0f),
                    vec2(1.0f, 0.0f),
                    -1.0f,
                    0xff00ff00
            },
            {
                    vec3(1.0f, 1.0f, 1.0f),
                    vec3(0.0f, 1.0f, 0.0f),
                    vec2(1.0f, 1.0f),
                    -1.0f,
                    0xff00ff00
            },
            {
                    vec3(1.0f, 1.0f, 0.0f),
                    vec3(0.0f, 1.0f, 0.0f),
                    vec2(0.0f, 1.0f),
                    -1.0f,
                    0xff00ff00
            },
            // bottom face
            {
                    vec3(0.0f, 0.0f, 0.0f),   // position
                    vec3(0.0f, -1.0f, 0.0f),   // normal
                    vec2(0.0f, 0.0f),    // tex coords
                    -1.0f,  // tex slot
                    0xff00ff00  // color - green
            },
            {
                    vec3(1.0f, 0.0f, 0.0f),
                    vec3(0.0f, -1.0f, 0.0f),
                    vec2(1.0f, 0.0f),
                    -1.0f,
                    0xff00ff00
            },
            {
                    vec3(1.0f, 0.0f, 1.0f),
                    vec3(0.0f, -1.0f, 0.0f),
                    vec2(1.0f, 1.0f),
                    -1.0f,
                    0xff00ff00
            },
            {
                    vec3(0.0f, 0.0f, 1.0f),
                    vec3(0.0f, -1.0f, 0.0f),
                    vec2(0.0f, 1.0f),
                    -1.0f,
                    0xff00ff00
            },
    };

    uint16_t cube_indices[] {0, 1, 2, 2, 3, 0,
                             4, 5, 6, 6, 7, 4,
                             8, 9, 10, 10, 11, 8,
                             12, 13, 14, 14, 15, 12,
                             16, 17, 18, 18, 19, 16,
                             20, 21, 22, 22, 23, 20};
}
