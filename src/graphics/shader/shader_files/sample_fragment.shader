#version 460

in vec2 v_tex_coord;
in float v_tex_slot;
in vec4 v_color;

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

//vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_direction)
//{
//    vec3 light_direction = normalize(-light.direction);
//    // diffuse shading
//    float diff = max(dot(normal, light_direction), 0.0);
//
//    // specular shading
//    vec3 reflect_direction = reflect(-light_direction, normal);
//    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
//
//    // combine results
//    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    return (ambient + diffuse + specular);
//}

uniform sampler2D[32] textures;
uniform Material[32] materials;
uniform Light[32] lights;

void main()
{
    if (v_tex_slot >= 0.0f) {
        uint slot = uint(v_tex_slot + 0.5f);
        vec4 tex_color = texture(textures[slot], v_tex_coord);
        f_color = tex_color;
    }
    else {
        f_color = v_color;
    }
}
