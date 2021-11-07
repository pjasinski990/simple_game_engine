#include <fstream>
#include <sstream>
#include <cstdio>

#include <glad/glad.h>

#include "shader.h"
#include "../../utils/logger.h"

namespace mrld
{
    std::unordered_map<ShaderType, const char*> Shader::_shader_type_to_string = {
            {VERTEX_SHADER, "VERTEX_SHADER"},
            {GEOMETRY_SHADER, "GEOMETRY_SHADER"},
            {FRAGMENT_SHADER, "FRAGMENT_SHADER"}
    };

    Shader::Shader()
    {
        _shader_program = glCreateProgram();
    }

    Shader::Shader(const char *vertex_path, const char *fragment_path)
    {
        _shader_program = glCreateProgram();
        update_shader_source(vertex_path, VERTEX_SHADER);
        update_shader_source(fragment_path, FRAGMENT_SHADER);
    }

    Shader::Shader(const char *vertex_path, const char *geometry_path, const char *fragment_path)
    {
        _shader_program = glCreateProgram();
        update_shader_source(vertex_path, VERTEX_SHADER);
        update_shader_source(geometry_path, GEOMETRY_SHADER);
        update_shader_source(fragment_path, FRAGMENT_SHADER);
    }

    Shader::~Shader()
    {
        glDeleteProgram(_shader_program);
    }

    void Shader::update_shader_source(const char *path, ShaderType type)
    {
        std::ifstream file;
        try
        {
            file.open(path);
            if (!file.is_open()) {
                char msg[LOGGER_SHADER_ERR_MSG_MAX_LENGTH];
                // TODO this code is being repeated a lot. move to function.
                int sprintf_res = sprintf_s(msg,
                          LOGGER_SHADER_ERR_MSG_MAX_LENGTH,
                          "Error loading shader source file. File %s cannot be open for reading", path);
                if (sprintf_res == -1) {
                    Logger::log(LogLevel::ERR, "%s", "Error updating shader source. Could not retrieve error message.");
                }
                else {
                    Logger::log(LogLevel::ERR, "%s", msg);
                }
                throw std::runtime_error("Error loading shader file");
            }
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();

            switch (type) {
                case VERTEX_SHADER:
                    _vertex_shader_source = stream.str();
                    break;
                case GEOMETRY_SHADER:
                    _geometry_shader_source = stream.str();
                    break;
                case FRAGMENT_SHADER:
                    _fragment_shader_source = stream.str();
                    break;
            }
        }
        catch (std::ifstream::failure& e) {
            char msg[LOGGER_SHADER_ERR_MSG_MAX_LENGTH];
            int sprintf_res = sprintf_s(msg,
                      LOGGER_SHADER_ERR_MSG_MAX_LENGTH,
                      "Error loading shader of type %s from file %s",
                    _shader_type_to_string[type], path);
            if (sprintf_res == -1) {
                Logger::log(LogLevel::ERR, "%s", "Error updating shader source. Could not retrieve error message.");
            }
            else {
                Logger::log(LogLevel::ERR, "%s", msg);
            }
            throw e;
        }
    }

    void Shader::create_shader_program()
    {
        initialize_shaders();

        GLint success;
        GLchar msg[LOGGER_SHADER_ERR_MSG_MAX_LENGTH];
        glAttachShader(_shader_program, _vertex_shader);
        glAttachShader(_shader_program, _fragment_shader);
        if (!_geometry_shader_source.empty()) {
            glAttachShader(_shader_program, _fragment_shader);
        }
        glLinkProgram(_shader_program);
        glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(_shader_program, LOGGER_SHADER_ERR_MSG_MAX_LENGTH, nullptr, msg);
            char err_msg[LOGGER_SHADER_ERR_MSG_MAX_LENGTH];
            int sprintf_res = sprintf_s(err_msg,
                      LOGGER_SHADER_ERR_MSG_MAX_LENGTH,
                      "Error: shader linking failed. \nFull error message:\n%s", msg);
            if (sprintf_res == -1) {
                Logger::log(LogLevel::ERR, "%s", "Error updating shader source. Could not retrieve error message.");
            }
            else {
                Logger::log(LogLevel::ERR, "%s", err_msg);
            }
            throw std::runtime_error("Error linking shader");
        }
        glValidateProgram(_shader_program);
        glGetProgramiv(_shader_program, GL_VALIDATE_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(_shader_program, LOGGER_SHADER_ERR_MSG_MAX_LENGTH, nullptr, msg);
            char err_msg[LOGGER_SHADER_ERR_MSG_MAX_LENGTH];
            int sprintf_res = sprintf_s(err_msg,
                      LOGGER_SHADER_ERR_MSG_MAX_LENGTH,
                      "Error: shader validation failed. \nFull error message:\n%s", msg);
            if (sprintf_res == -1) {
                Logger::log(LogLevel::ERR, "%s", "Error creating shader program. Could not retrieve error message.");
            }
            else {
                Logger::log(LogLevel::ERR, "%s", err_msg);
            }
            throw std::runtime_error("Error linking shader");
        }

        // TODO this is very bad. remove magic numbers, possibly create global config, add
        // function to set array of uniforms. also, this should be extracted to member function.
        int slots[32];
        for (int i = 0; i < 32; ++i) {
            slots[i] = i;
        }
        use();
        glUniform1iv(get_uniform_location("textures"), 32, slots);
        disable();

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

    void Shader::set_bool(const char *name, bool value) const
	{
        glUniform1i(get_uniform_location(name), (int)value);
	}
    void Shader::set_int(const char *name, int value) const
	{
        glUniform1i(get_uniform_location(name), value);
	}
    void Shader::set_float(const char *name, float value) const
	{
        glUniform1f(get_uniform_location(name), value);
	}
    void Shader::set_mat4(const char *name, const mat4 &value) const
	{
        glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, value.data);
	}
    void Shader::set_vec2(const char *name, const vec2 &value) const
	{
        glUniform2f(get_uniform_location(name), value.x, value.y);
	}
    void Shader::set_vec3(const char *name, const vec3 &value) const
	{
        glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
	}
    void Shader::set_vec4(const char *name, const vec4 &value) const
	{
        glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
	}

    unsigned int Shader::compile_shader(const char *source_str, GLenum type)
    {
        GLint success;
        GLchar msg[LOGGER_SHADER_ERR_MSG_MAX_LENGTH];

        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source_str, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, LOGGER_SHADER_ERR_MSG_MAX_LENGTH, nullptr, msg);
            char err_msg[LOGGER_SHADER_ERR_MSG_MAX_LENGTH];
            int sprintf_res = sprintf_s(err_msg,
                      LOGGER_SHADER_ERR_MSG_MAX_LENGTH,
                      "Error: %s compilation failed. \nFull error message:\n%s",
                    _shader_type_to_string[static_cast<ShaderType>(type)], msg);
            if (sprintf_res == -1) {
                Logger::log(LogLevel::ERR, "%s", "Error compiling shader. Could not retrieve error message.");
            }
            else {
                Logger::log(LogLevel::ERR, "%s", err_msg);
            }
            throw std::runtime_error("Error compiling shader");
        }
        return shader;
    }
    void Shader::initialize_shaders()
    {
        if (_vertex_shader_source.empty() || _fragment_shader_source.empty()) {
            Logger::log(LogLevel::WRN, "%s",
                        "Not initializing shaders - at least vertex and fragment shaders must be loaded");
            return;
        }

        _vertex_shader = compile_shader(_vertex_shader_source.c_str(), GL_VERTEX_SHADER);
        _fragment_shader = compile_shader(_fragment_shader_source.c_str(), GL_FRAGMENT_SHADER);
        if (!_geometry_shader_source.empty()) {
            _geometry_shader = compile_shader(_geometry_shader_source.c_str(), GL_GEOMETRY_SHADER);
        }
    }

    GLuint Shader::get_uniform_location(const char *name) const
    {
        return glGetUniformLocation(_shader_program, name);
    }
}
