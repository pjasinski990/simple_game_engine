#pragma once

#include <string>
#include <unordered_map>

#include "../graphics/materials/material.h"

namespace mrld
{
    class Model;
    namespace ObjModelParser
    {
        Model parse_obj_to_model(const std::string &obj_filepath);
        Model parse_obj_to_model(const std::string &obj_filepath, const std::string &mtl_filepath);
        Model parse_obj_to_model(const std::string &obj_filepath, std::vector<material> materials);

        std::vector<material> parse_mtl_to_materials(const std::string &filepath);
    }
}
