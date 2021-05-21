#include <fstream>
#include <sstream>
#include <cstdio>

#include <glad/glad.h>

#include <graphics/shader.h>

namespace mrld
{
    std::unordered_map<ShaderType, const char*> Shader::_shader_type_to_string = {
            {VERTEX_SHADER, "VERTEX_SHADER"},
            {GEOMETRY_SHADER, "GEOMETRY_SHADER"},
            {FRAGMENT_SHADER, "FRAGMENT_SHADER"}
    };

    Shader::Shader() = default;

    Shader::Shader(const char *vertex_path, const char *fragment_path)
    {
        update_shader_source(vertex_path, VERTEX_SHADER);
        update_shader_source(fragment_path, FRAGMENT_SHADER);
    }

    Shader::Shader(const char *vertex_path, const char *geometry_path, const char *fragment_path)
    {
        update_shader_source(vertex_path, VERTEX_SHADER);
        update_shader_source(geometry_path, GEOMETRY_SHADER);
        update_shader_source(fragment_path, FRAGMENT_SHADER);
    }

    Shader::~Shader() = default;

    void Shader::update_shader_source(const char *path, ShaderType type)
    {
        std::ifstream file;
        try
        {
            file.open(path);
            if (!file.is_open()) {
                char msg[512];
                sprintf(msg, "Error loading shader source file. File %s cannot be open for reading.", path);
                throw ShaderException(msg);
            }
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();

            switch (type) {
                case VERTEX_SHADER:
                    _vertex_shader_source = stream.str();
                    std::cout << _vertex_shader_source;
                    break;
                case GEOMETRY_SHADER:
                    _geometry_shader_source = stream.str();
                    std::cout << _geometry_shader_source;
                    break;
                case FRAGMENT_SHADER:
                    _fragment_shader_source = stream.str();
                    std::cout << _fragment_shader_source;
                    break;
            }
        }
        catch (std::ifstream::failure& e) {
            char msg[512];
            sprintf(msg, "Error loading shader of type %s from file %s.",
                    _shader_type_to_string[type], path);
            throw ShaderException(msg);
        }
    }

    void Shader::create_shader_program()
    {
        initialize_shaders();

        _shader_program = glCreateProgram();

        GLint success;
        GLchar msg[512];
        glAttachShader(_shader_program, _vertex_shader);
        glAttachShader(_shader_program, _fragment_shader);
        if (!_geometry_shader_source.empty()) {
            glAttachShader(_shader_program, _fragment_shader);
        }
        glLinkProgram(_shader_program);
        glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(_shader_program, 512, nullptr, msg);
            char exc_msg[512];
            sprintf(exc_msg, "Error: shader linking failed. \nFull error message:\n%s", msg);
            throw ShaderException(exc_msg);
        }
        glDeleteShader(_vertex_shader);
        glDeleteShader(_fragment_shader);
    }
    void Shader::use() const
    {
        glUseProgram(_shader_program);
    }
    void Shader::disable() const
    {
        glUseProgram(0);
    }

    unsigned int Shader::compile_shader(const char *source_str, GLenum type)
    {
        GLint success;
        GLchar msg[512];

        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source_str, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 512, nullptr, msg);
            char exc_msg[512];
            sprintf(exc_msg, "Error: %s compilation failed. \nFull error message:\n%s",
                    _shader_type_to_string[static_cast<ShaderType>(type)], msg);
            throw ShaderException(exc_msg);
        }
        return shader;
    }
    void Shader::initialize_shaders()
    {
        if (_vertex_shader_source.empty() || _fragment_shader_source.empty()) {
            throw ShaderException("Error initializing shaders: at least vertex and fragment shaders must be loaded.");
        }

        _vertex_shader = compile_shader(_vertex_shader_source.c_str(), GL_VERTEX_SHADER);
        _fragment_shader = compile_shader(_fragment_shader_source.c_str(), GL_FRAGMENT_SHADER);
        if (!_geometry_shader_source.empty()) {
            _geometry_shader = compile_shader(_geometry_shader_source.c_str(), GL_GEOMETRY_SHADER);
        }
    }
}
