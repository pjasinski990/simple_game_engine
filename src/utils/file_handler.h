#pragma once

#include <string>

namespace mrld
{
    class FileHandler
    {
    public:
        static std::string read_file_contents(const char *filepath);
    };
}