#include <fstream>
#include <sstream>
#include <regex>

#include "obj_model_parser.h"
#include "logger.h"
#include "../graphics/rendering/renderable/drawable/model.h"

namespace mrld
{
    namespace ObjModelParser
    {
        Model *parse_obj_to_model(const std::string &filepath)
        {
            std::vector<vec3> positions;
            std::vector<vec3> normals;
            std::vector<vec2> tex_coords;
            std::vector<uint32_t> indices_positions;
            std::vector<uint32_t> indices_normals;
            std::vector<uint32_t> indices_tex_coords;

            std::vector<material> materials;
            std::vector<uint16_t> material_indices;
            int32_t current_material_index = -1;
            bool has_materials;

            std::ifstream fin(filepath);
            if (!fin) {
                Logger::log(LogLevel::ERR, "File %s could not be opened for reading", filepath.c_str());
                return nullptr;
            }

            std::string line;
            while (std::getline(fin, line)) {
                std::istringstream ss(line);
                std::string msg;

                ss >> msg;
                if (msg == "mtllib") {
                    std::string filepath_mtl = filepath.substr(0, filepath.find(".obj")).append(".mtl");
                    Logger::log(LogLevel::DBG, "Trying to load material file for %s from %s", filepath.c_str(), filepath_mtl.c_str());
                    materials = parse_mtl_to_materials(filepath_mtl);
                    has_materials = true;
                }
                else if (msg == "v") {
                    float x, y, z;
                    ss >> x >> y >> z;
                    positions.push_back(vec3(x, y, z));
                }
                else if (msg == "vn") {
                    float x, y, z;
                    ss >> x >> y >> z;
                    normals.push_back(vec3(x, y, z));
                }
                else if (msg == "vt") {
                    float x, y, z;
                    ss >> x >> y >> z;
                    tex_coords.push_back(vec2(x, y));
                }
                else if (msg == "usemtl") {
                    std::string name;
                    ss >> name;
                    current_material_index = std::find_if(materials.begin(), materials.end(),
                                                          [&](material& m){ return m.name == name; }) - std::begin(materials);
                }
                else if (msg == "f") {
                    line = std::regex_replace(line, std::regex("/"), " ");
                    ss.clear();
                    ss.str(line);
                    uint16_t p1, p2, p3, t1, t2, t3, n1, n2, n3;
                    ss >> msg >> p1 >> t1 >> n1 >> p2 >> t2 >> n2 >> p3 >> t3 >> n3;

                    indices_positions.push_back(p1 - 1);
                    indices_positions.push_back(p2 - 1);
                    indices_positions.push_back(p3 - 1);

                    indices_tex_coords.push_back(t1 - 1);
                    indices_tex_coords.push_back(t2 - 1);
                    indices_tex_coords.push_back(t3 - 1);

                    indices_normals.push_back(n1 - 1);
                    indices_normals.push_back(n2 - 1);
                    indices_normals.push_back(n3 - 1);

                    material_indices.push_back(current_material_index);
                    material_indices.push_back(current_material_index);
                    material_indices.push_back(current_material_index);
                }
            }

            VertexData *res_vertices = new VertexData[indices_positions.size()];
            uint16_t *res_indices = new uint16_t[indices_positions.size()];
            for (int i = 0; i < indices_positions.size(); ++i) {
                VertexData next;
                next.position = positions[indices_positions[i]];
                next.tex_coord = tex_coords[indices_tex_coords[i]];
                next.normal = normals[indices_normals[i]];
                next.tex_slot = -1.0f;
                if (has_materials) {
                    vec3 color = materials[material_indices[i]].diffuse;
                    uint8_t r = static_cast<uint8_t>(color.x * 255.0f);
                    uint8_t g = static_cast<uint8_t>(color.y * 255.0f);
                    uint8_t b = static_cast<uint8_t>(color.z * 255.0f);
                    uint8_t a = static_cast<uint8_t>(materials[material_indices[i]].dissolve * 255.0f);
                    next.color = a << 24 | b << 16 | g << 8 | r;
                }
                res_vertices[i] = next;
                res_indices[i] = i;
            }
            return new Model(res_vertices, indices_positions.size(), res_indices, indices_positions.size());
        }

        std::vector<material> parse_mtl_to_materials(const std::string &filepath)
        {
            std::vector<material> result;
            std::ifstream fin(filepath);
            if (!fin) {
                Logger::log(LogLevel::ERR, "File %s could not be opened for reading", filepath.c_str());
                Logger::log(LogLevel::WRN, "Returning empty materials");
                return result;
            }

            std::string line;
            while (std::getline(fin, line)) {
                std::istringstream ss(line);
                std::string msg;

                ss >> msg;
                if (msg == "newmtl") {
                    result.push_back(material());
                    ss >> result.back().name;
                }
                else if (msg == "Ns") {
                    float ns;
                    ss >> ns;
                    result.back().specular_e = ns;
                }
                else if (msg == "Ka") {
                    float x, y, z;
                    ss >> x >> y >> z;
                    result.back().ambient = vec3(x, y, z);
                }
                else if (msg == "Kd") {
                    float x, y, z;
                    ss >> x >> y >> z;
                    result.back().diffuse = vec3(x, y, z);
                }
                else if (msg == "Ks") {
                    float x, y, z;
                    ss >> x >> y >> z;
                    result.back().specular = vec3(x, y, z);
                }
                else if (msg == "d") {
                    float d;
                    ss >> d;
                    result.back().dissolve = d;
                }
            }
            return result;
        }

    }
}
