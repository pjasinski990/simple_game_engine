#pragma once

namespace mrld
{
    enum class TextureType {
        TEXTURE_DIFFUSE,
        TEXTURE_SPECULAR
    };

    class Texture
    {
    public:
        Texture(const char *filename, bool reverse = false, TextureType type = TextureType::TEXTURE_DIFFUSE);
        ~Texture();
        void bind(uint32_t slot = 0) const;
        void unbind() const;

        inline uint32_t get_width() const { return _width; }
        inline uint32_t get_height() const { return _height; }
        inline uint32_t get_id() const { return _id; }
    private:
        std::string _filename;
        TextureType _type;
        uint32_t _id;
        int32_t _width;
        int32_t _height;
        int32_t _n_channels;
    };
}
