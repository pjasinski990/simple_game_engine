#pragma once

namespace mrld
{
    // TODO make renderables take textures allocated on heap? unify allocation and freeing of memory across the project
    class Texture
    {
    public:
        Texture(const char *filename, bool reverse = false);
        ~Texture();
        void bind(uint32_t slot = 0) const;
        void unbind() const;

        inline uint32_t get_width() const { return _width; }
        inline uint32_t get_height() const { return _height; }
        inline uint32_t get_id() const { return _id; }
    private:
        std::string _filename;
        uint32_t _id;
        int32_t _width;
        int32_t _height;
        int32_t _n_channels;
    };
}
