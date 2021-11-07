#pragma once

#include "glad/glad.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"
#include "../../math/mat4.h"

namespace mrld
{
    enum ShaderType
    {
        VERTEX_SHADER = GL_VERTEX_SHADER,
        GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };

    class Shader
    {
    public:
        Shader();
        Shader(const char *vertex_path, const char *fragment_path);
        Shader(const char *vertex_path, const char *geometry_path, const char *fragment_path);
        ~Shader();

        void update_shader_source(const char *path, ShaderType type);
        void create_shader_program();
        void use() const;
        void disable() const;

        // TODO cache uniform names against ids
        void set_bool(const char *name, bool value) const;
        void set_int(const char *name, int value) const;
        void set_float(const char *name, float value) const;
        void set_mat4(const char *name, const mat4 &value) const;
        void set_vec2(const char *name, const vec2 &value) const;
        void set_vec3(const char *name, const vec3 &value) const;
        void set_vec4(const char *name, const vec4 &value) const;
        // TODO this should be private
        GLuint get_uniform_location(const char *name) const;

    private:
        GLuint compile_shader(const char *source_str, GLenum type);
        void initialize_shaders();

        static std::unordered_map<ShaderType, const char*> _shader_type_to_string;

        std::string _vertex_shader_source;
        std::string _geometry_shader_source;
        std::string _fragment_shader_source;
        GLuint _vertex_shader;
        GLuint _geometry_shader;
        GLuint _fragment_shader;
    public:
        GLuint _shader_program;
    };
}
