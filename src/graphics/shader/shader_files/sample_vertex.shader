#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
layout (location = 3) in float tex_slot;
layout (location = 4) in vec4 color;

uniform mat4 proj_matrix;
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out vec4 v_pos;
out vec2 v_tex_coord;
out float v_tex_slot;
out vec4 v_color;

void main()
{
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0f);

    v_pos = model_matrix * vec4(position, 1.0f);
    v_tex_coord = tex_coord;
    v_tex_slot = tex_slot;
    v_color = color;
}
