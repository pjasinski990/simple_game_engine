#version 330 core

in vec4 v_pos;
in vec2 v_tex_coord;
in float v_tex_index;
in vec4 v_color;

out vec4 f_color;

uniform vec2 light_position;
uniform sampler2D tex;

void main()
{
    vec4 tex_color = texture(tex, v_tex_coord);
//    f_color = tex_color * vec4(v_color.xyz, 1.0f);
    f_color = tex_color;
//    f_color = vec4(v_color.xyz, 1.0f);
}
