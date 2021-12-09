#include <glad/glad.h>

#include "shader.h"
#include "../../utils/logger.h"
#include "../../utils/file_handler.h"
#include "../lighting/point_light.h"
#include "../lighting/directional_light.h"

namespace mrld
{
    std::unordered_map<ShaderType, const char*> Shader::_shader_type_to_string = {
            {ShaderType::VERTEX_SHADER, "VERTEX_SHADER"},
            {ShaderType::GEOMETRY_SHADER, "GEOMETRY_SHADER"},
            {ShaderType::FRAGMENT_SHADER, "FRAGMENT_SHADER"}
    };

    Shader::Shader()
    {
        _shader_program = glCreateProgram();
    }

    Shader::Shader(const char *vertex_path, const char *fragment_path)
    {
        _shader_program = glCreateProgram();
        update_shader_source(vertex_path, ShaderType::VERTEX_SHADER);
        update_shader_source(fragment_path, ShaderType::FRAGMENT_SHADER);
    }

    Shader::Shader(const char *vertex_path, const char *geometry_path, const char *fragment_path)
    {
        _shader_program = glCreateProgram();
        update_shader_source(vertex_path, ShaderType::VERTEX_SHADER);
        update_shader_source(geometry_path, ShaderType::GEOMETRY_SHADER);
        update_shader_source(fragment_path, ShaderType::FRAGMENT_SHADER);
    }

    Shader::~Shader()
    {
        glDeleteProgram(_shader_program);
    }

    void Shader::update_shader_source(const char *path, ShaderType type)
    {
        std::string source = FileHandler::read_file_contents(path);
        switch (type) {
            case ShaderType::VERTEX_SHADER:
                _vertex_shader_source = source;
                break;
            case ShaderType::GEOMETRY_SHADER:
                _geometry_shader_source = source;
                break;
            case ShaderType::FRAGMENT_SHADER:
                _fragment_shader_source = source;
                break;
        }
    }

    void Shader::create_shader_program(uint32_t n_texture_slots /* = 32 */)
    {
        initialize_shaders();

        glAttachShader(_shader_program, _vertex_shader);
        glAttachShader(_shader_program, _fragment_shader);
        if (!_geometry_shader_source.empty()) {
            glAttachShader(_shader_program, _fragment_shader);
        }

        link_shaders();
        validate_shaders();
        initialize_texture_slots(n_texture_slots);

        glDeleteShader(_vertex_shader);
        glDeleteShader(_fragment_shader);
        if (!_geometry_shader_source.empty()) {
            glDeleteShader(_geometry_shader);
        }
    }

    void Shader::use() const
    {
        glUseProgram(_shader_program);
    }
    void Shader::disable() const
    {
        glUseProgram(0);
    }

    void Shader::set_bool(const char *name, bool value)
	{
        glUniform1i(get_uniform_location(name), (int)value);
	}
    void Shader::set_int(const char *name, int value)
	{
        glUniform1i(get_uniform_location(name), value);
	}
    void Shader::set_float(const char *name, float value)
	{
        glUniform1f(get_uniform_location(name), value);
	}
    void Shader::set_mat4(const char *name, const mat4 &value)
	{
        glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, value.data);
	}
    void Shader::set_vec2(const char *name, const vec2 &value)
	{
        glUniform2f(get_uniform_location(name), value.x, value.y);
	}
    void Shader::set_vec3(const char *name, const vec3 &value)
	{
        glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
	}
    void Shader::set_vec4(const char *name, const vec4 &value)
	{
        glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
	}

    unsigned int Shader::compile_shader(const char *source_str, GLenum type)
    {
        GLint success;
        GLchar msg[LOGGER_MESSAGE_MAX_LENGTH];

        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source_str, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, LOGGER_MESSAGE_MAX_LENGTH, nullptr, msg);
            char err_msg[LOGGER_MESSAGE_MAX_LENGTH];
            int sprintf_res = snprintf(err_msg,
                      LOGGER_MESSAGE_MAX_LENGTH,
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
                        "Not initializing shaders - at least vertex and fragment shaders sources must be loaded.");
            return;
        }

        _vertex_shader = compile_shader(_vertex_shader_source.c_str(), GL_VERTEX_SHADER);
        _fragment_shader = compile_shader(_fragment_shader_source.c_str(), GL_FRAGMENT_SHADER);
        if (!_geometry_shader_source.empty()) {
            _geometry_shader = compile_shader(_geometry_shader_source.c_str(), GL_GEOMETRY_SHADER);
        }
    }

    GLuint Shader::get_uniform_location(const char *name)
    {
        if (_uniform_name_to_id.contains(name)) {
            return _uniform_name_to_id.at(name);
        }
        uint32_t id = glGetUniformLocation(_shader_program, name);
        _uniform_name_to_id.insert(std::make_pair(name, id));
        return id;
    }

    void Shader::link_shaders()
    {
        GLint success;
        GLchar msg[LOGGER_MESSAGE_MAX_LENGTH];

        glLinkProgram(_shader_program);
        glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(_shader_program, LOGGER_MESSAGE_MAX_LENGTH, nullptr, msg);
            char err_msg[LOGGER_MESSAGE_MAX_LENGTH];
            int sprintf_res = snprintf(err_msg,
                                        LOGGER_MESSAGE_MAX_LENGTH,
                                        "Error: shader linking failed. \nFull error message:\n%s", msg);
            if (sprintf_res == -1) {
                Logger::log(LogLevel::ERR, "%s", "Error linking shader. Could not retrieve error message.");
            }
            else {
                Logger::log(LogLevel::ERR, "%s", err_msg);
            }
            throw std::runtime_error("Error linking shader");
        }
    }

    void Shader::validate_shaders()
    {
        GLint success;
        GLchar msg[LOGGER_MESSAGE_MAX_LENGTH];

        glValidateProgram(_shader_program);
        glGetProgramiv(_shader_program, GL_VALIDATE_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(_shader_program, LOGGER_MESSAGE_MAX_LENGTH, nullptr, msg);
            char err_msg[LOGGER_MESSAGE_MAX_LENGTH];
            int sprintf_res = snprintf(err_msg,
                                        LOGGER_MESSAGE_MAX_LENGTH,
                                        "Error: shader validation failed. \nFull error message:\n%s", msg);
            if (sprintf_res == -1) {
                Logger::log(LogLevel::ERR, "%s", "Error creating shader program. Could not retrieve error message.");
            }
            else {
                Logger::log(LogLevel::ERR, "%s", err_msg);
            }
            throw std::runtime_error("Error linking shader");
        }
    }

    void Shader::initialize_texture_slots(uint32_t n_texture_slots)
    {
        int *slots = new int[n_texture_slots];
        for (uint32_t i = 0; i < n_texture_slots; ++i) {
            slots[i] = i;
        }
        use();
        // technically it would be better to create a function to update 1iv uniform, cache id, use it here
        glUniform1iv(get_uniform_location("textures"), n_texture_slots, slots);
        disable();
        delete[] slots;
    }

    void Shader::set_material(const material &m, uint32_t index)
    {
        std::string prefix("materials[");
        std::string ambient_suffix("].ambient");
        std::string diffuse_suffix("].diffuse");
        std::string specular_suffix("].specular");
        std::string specular_e_suffix("].specular_e");
        std::string dissolve_suffix("].dissolve");

        std::string ambient_string = prefix + std::to_string(index) + ambient_suffix;
        std::string diffuse_string = prefix + std::to_string(index) + diffuse_suffix;
        std::string specular_string = prefix + std::to_string(index) + specular_suffix;
        std::string specular_e_string = prefix + std::to_string(index) + specular_e_suffix;
        std::string dissolve_string = prefix + std::to_string(index) + dissolve_suffix;

        use();
        set_vec3(ambient_string.c_str(), m.ambient);
        set_vec3(diffuse_string.c_str(), m.diffuse);
        set_vec3(specular_string.c_str(), m.specular);
        set_float(specular_e_string.c_str(), m.specular_e);
        set_float(dissolve_string.c_str(), m.dissolve);
    }

    void Shader::set_directional_light(const directional_light &l)
    {
        std::string direction_string = "directional_light.direction";
        std::string ambient_string = "directional_light.ambient";
        std::string diffuse_string = "directional_light.diffuse";
        std::string specular_string = "directional_light.specular";

        use();
        set_vec3(direction_string.c_str(), l.direction);
        set_vec3(ambient_string.c_str(), l.ambient);
        set_vec3(diffuse_string.c_str(), l.diffuse);
        set_vec3(specular_string.c_str(), l.specular);
    }

    void Shader::set_point_light(const point_light &l, uint32_t index)
    {
        std::string position_string = "point_lights[" + std::to_string(index) + "].position";
        std::string ambient_string = "point_lights[" + std::to_string(index) + "].ambient";
        std::string diffuse_string = "point_lights[" + std::to_string(index) + "].diffuse";
        std::string specular_string = "point_lights[" + std::to_string(index) + "].specular";

        std::string constant_string = "point_lights[" + std::to_string(index) + "].constant";
        std::string linear_string = "point_lights[" + std::to_string(index) + "].linear";
        std::string quadratic_string = "point_lights[" + std::to_string(index) + "].quadratic";

        use();
        set_vec3(position_string.c_str(), l.position);
        set_vec3(ambient_string.c_str(), l.ambient);
        set_vec3(diffuse_string.c_str(), l.diffuse);
        set_vec3(specular_string.c_str(), l.specular);

        set_float(constant_string.c_str(), l.constant);
        set_float(linear_string.c_str(), l.linear);
        set_float(quadratic_string.c_str(), l.quadratic);
    }
}
