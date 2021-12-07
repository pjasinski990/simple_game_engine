#version 460

in vec2 v_tex_coord;
in float v_tex_slot;
in float v_material_slot;

in vec3 v_position;
in vec3 v_normal;
in vec4 v_color;

in vec3 v_camera_position;
in vec3 v_camera_direction;

out vec4 f_color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float specular_e;
    float dissolve;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D[32] textures;
uniform Material[32] materials;
uniform Light[32] lights;

void main()
{
    vec3 light_pos = vec3(3.0f, 2.0f, 0.0f);
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);

    vec3 light_direction = normalize(light_pos - v_position);
    float diff = max(dot(v_normal, light_direction), 0.0f);
    vec3 reflect_direction = reflect(-1.0f * light_direction, v_normal);
    vec3 view_direction = normalize(v_camera_position - v_position);

    vec3 ambient = vec3(1.0f);
    vec3 diffuse = vec3(1.0f);
    vec4 color = vec4(1.0f);

    if (v_tex_slot >= 0.0f) {
        uint t_slot = uint(v_tex_slot + 0.5f);
        vec4 tex_color = texture(textures[t_slot], v_tex_coord);
        ambient = light_color * tex_color.xyz;
        diffuse = light_color * (diff * tex_color.xyz);

        color = tex_color * vec4(ambient + diffuse, 1.0f);
    }

    if (v_material_slot >= 0.0f) {
        uint m_slot = uint(v_material_slot + 0.5f);
        Material material = materials[m_slot];

        ambient *= light_color * material.ambient;
        diffuse *= light_color * (diff * material.diffuse);
        float spec = pow(max(dot(view_direction, reflect_direction), 0.0f), material.specular_e);
        vec3 specular = light_color * (spec * material.specular);

        color *= vec4(ambient + diffuse + specular, material.dissolve);
    }
    else if (v_tex_slot < 0.0f) {
        ambient = light_color * v_color.xyz;
        diffuse = light_color * (diff * v_color.xyz);
        color = v_color * vec4(ambient + diffuse, 1.0f);
    }

    f_color = color;

//    // Has materials
//        if (v_material_slot >= 0.0f) {
//        }
//        // Texture, no materials
//        else {
//            vec3 ambient = light_color * tex_color.xyz;
//            vec3 diffuse = light_color * (diff * tex_color.xyz);
//            f_color = tex_color * vec4(ambient + diffuse, 1.0f);
//        }
//    }
//    // Materials, no texture
//    else if (v_material_slot >= 0.0f) {
//        vec3 ambient = light_color * material.ambient;
//        vec3 diffuse = light_color * (diff * material.diffuse);
//        float spec = pow(max(dot(view_direction, reflect_direction), 0.0f), material.specular_e);
//        vec3 specular = light_color * (spec * material.specular);
//
//        f_color = vec4(ambient + diffuse + specular, material.dissolve);
//    }
//    // No texture or materials, fall back on color
//    else {
//        vec3 ambient = light_color * v_color.xyz;
//        vec3 diffuse = light_color * (diff * v_color.xyz);
//        float spec = pow(max(dot(view_direction, reflect_direction), 0.0f), 32.0f);
//        vec3 specular = light_color * (spec * v_color.xyz);
//        f_color = vec4(ambient + diffuse + specular, v_color.w);
//    }
}
