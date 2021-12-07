#pragma once

#include <string>
#include "../graphics/materials/material.h"

namespace mrld
{
    class Model;
    namespace ObjModelParser
    {
        Model *parse_obj_to_model(const std::string &filepath);
        std::vector<material> parse_mtl_to_materials(const std::string &filepath);

    }
}
