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
        Shader(const std::string &vertex_path, const std::string &fragment_path);
        Shader(const std::string &vertex_path, const std::string &geometry_path, const std::string &fragment_path);
        ~Shader();

        void update_shader_source(const std::string &path, ShaderType type);
        void create_shader_program();
        void use() const;

    private:
        unsigned int compile_shader(const char *source_str, GLenum type);
        void initialize_shaders();

        static std::unordered_map<ShaderType, const char*> _shader_type_to_string;

        std::string _vertex_shader_source;
        std::string _geometry_shader_source;
        std::string _fragment_shader_source;
        unsigned int _vertex_shader;
        unsigned int _geometry_shader;
        unsigned int _fragment_shader;
        unsigned int _shader_program;
    };

    class ShaderException: public std::runtime_error {
    public:
        explicit ShaderException(const char* msg): std::runtime_error(msg) {}
        virtual ~ShaderException() = default;
        virtual const char *what() const noexcept override { return runtime_error::what(); }
    };
}

#endif //MRLD_ENGINE_SHADER_H
