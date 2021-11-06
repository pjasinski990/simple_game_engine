#include <string>

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../dependencies/stb_image/stb_image.h"
#include "../../utils/logger.h"

#include "texture.h"

namespace mrld
{
    Texture::Texture(const char *filename, uint32_t slot /* = 0 */, bool reverse /* = false */)
    : _filename{filename}
    {
        stbi_set_flip_vertically_on_load(reverse);
        unsigned char *tex_data_buffer = stbi_load(_filename.c_str(), &_width, &_height, &_n_channels, 4);
        if (!tex_data_buffer) {
            Logger::log(LogLevel::ERR, "Error loading texture %s", filename);
        }
        else {
            glGenTextures(1, &_id);
            bind(slot);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data_buffer);
            glGenerateMipmap(GL_TEXTURE_2D);
            unbind();
        }
        stbi_image_free(tex_data_buffer);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &_id);
    }

    void Texture::bind(uint32_t slot /* = 0 */) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
