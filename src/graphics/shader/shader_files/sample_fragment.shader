#version 330 core

in vec4 v_pos;
in vec4 v_color;
out vec4 f_color;

uniform vec2 light_position;

void main()
{
    float brightness = 1.0f / length(v_pos.xy - light_position) * 0.5;
    f_color = v_color * brightness;
}
