#ifndef MRLD_ENGINE_SHADER_H
#define MRLD_ENGINE_SHADER_H

#include <iostream>
#include <string>
#include <unordered_map>

namespace mrld
{
    enum ShaderType {
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
        GLuint _shader_program;
    };

    class ShaderException: public std::runtime_error {
    public:
        explicit ShaderException(const char* msg): std::runtime_error(msg) {}
        virtual ~ShaderException() = default;
        virtual const char *what() const noexcept override { return runtime_error::what(); }
    };
}

#endif //MRLD_ENGINE_SHADER_H
