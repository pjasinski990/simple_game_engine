#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 proj_matrix;
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);


void main()
{
    gl_Position = /* proj_matrix * view_matrix * model_matrix * */ vec4(pos, 1.0);
}
