#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

#include "obj_model_parser.h"
#include "logger.h"
#include "../graphics/rendering/renderable/drawable/model.h"

namespace mrld
{
    namespace ObjModelParser
    {
        Model parse_obj_to_model(const std::string &obj_filepath)
        {
            std::vector<vec3> positions;
            std::vector<vec3> normals;
            std::vector<vec2> tex_coords;
            std::vector<uint32_t> indices_positions;
            std::vector<uint32_t> indices_normals;
            std::vector<uint32_t> indices_tex_coords;

            std::ifstream fin(obj_filepath);
            if (!fin) {
                Logger::log(LogLevel::ERR, "File %s could not be opened for reading", obj_filepath.c_str());
                throw std::runtime_error("Error loading model");
            }

            std::string line;
            while (std::getline(fin, line)) {
                std::istringstream ss(line);
                std::string msg;

                ss >> msg;
                if (msg == "mtllib") {
                    std::string filepath_mtl = obj_filepath.substr(0, obj_filepath.find(".obj")).append(".mtl");
                    Logger::log(LogLevel::INF,
                                "Model %s has materials but no materials were provided. Continuing without materials", obj_filepath.c_str());
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
                    float x, y;
                    ss >> x >> y;
                    tex_coords.push_back(vec2(x, y));
                }
                else if (msg == "f") {
                    line = std::regex_replace(line, std::regex("/"), " ");
                    ss.clear();
                    ss.str(line);
                    uint16_t p1, p2, p3, t1, t2, t3, n1, n2, n3;
                    if (!tex_coords.empty()) {
                        ss >> msg >> p1 >> t1 >> n1 >> p2 >> t2 >> n2 >> p3 >> t3 >> n3;
                    }
                    else {
                        ss >> msg >> p1 >> n1 >> p2 >> n2 >> p3 >> n3;
                    }

                    indices_positions.push_back(p1 - 1);
                    indices_positions.push_back(p2 - 1);
                    indices_positions.push_back(p3 - 1);

                    if (!tex_coords.empty()) {
                        indices_tex_coords.push_back(t1 - 1);
                        indices_tex_coords.push_back(t2 - 1);
                        indices_tex_coords.push_back(t3 - 1);
                    }

                    indices_normals.push_back(n1 - 1);
                    indices_normals.push_back(n2 - 1);
                    indices_normals.push_back(n3 - 1);
                }
            }
            Logger::log(LogLevel::DBG, "Finished scanning file %s, now creating vertex data", obj_filepath.c_str());

            auto res_vertices = std::vector<VertexData>(indices_positions.size());
            auto res_indices = std::vector<uint16_t>(indices_positions.size());
            for (uint32_t i = 0; i < indices_positions.size(); ++i) {
                VertexData next;
                next.position = positions[indices_positions[i]];
                if (!tex_coords.empty()) {
                    next.tex_coord = tex_coords[indices_tex_coords[i]];
                }
                next.normal = normals[indices_normals[i]];
                next.tex_slot = -1.0f;
                next.material_slot = -1.0f;
                res_vertices[i] = next;
                res_indices[i] = i;
            }
            Logger::log(LogLevel::DBG, "Success");
            return Model(&res_vertices[0], indices_positions.size(), &res_indices[0], indices_positions.size());
        }

        Model parse_obj_to_model(const std::string &obj_filepath, const std::string &mtl_filepath)
        {
            std::vector<vec3> positions;
            std::vector<vec3> normals;
            std::vector<vec2> tex_coords;
            std::vector<uint32_t> indices_positions;
            std::vector<uint32_t> indices_normals;
            std::vector<uint32_t> indices_tex_coords;

            std::vector<material> materials;
            std::vector<uint16_t> indices_materials;
            int32_t current_material_index = -1;
            bool has_materials;

            std::ifstream fin(obj_filepath);
            if (!fin) {
                Logger::log(LogLevel::ERR, "File %s could not be opened for reading", obj_filepath.c_str());
                throw std::runtime_error("Error loading model");
            }

            std::string line;
            while (std::getline(fin, line)) {
                std::istringstream ss(line);
                std::string msg;

                ss >> msg;
                if (msg == "mtllib") {
                    Logger::log(LogLevel::DBG, "Trying to load material file for %s from %s", obj_filepath.c_str(), mtl_filepath.c_str());
                    materials = parse_mtl_to_materials(mtl_filepath);
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
                    float x, y;
                    ss >> x >> y;
                    tex_coords.push_back(vec2(x, y));
                }
                else if (msg == "usemtl") {
                    std::string name;
                    ss >> name;
                    current_material_index = std::find_if(materials.begin(),
                                                          materials.end(),
                                                          [&](material& m){ return m.name == name; }) - std::begin(materials);
                    Logger::log(LogLevel::DBG, "Starting to load model vertices with material %s (detected index: %d)",
                                name.c_str(), current_material_index);
                }
                else if (msg == "f") {
                    line = std::regex_replace(line, std::regex("/"), " ");
                    ss.clear();
                    ss.str(line);
                    uint16_t p1, p2, p3, t1, t2, t3, n1, n2, n3;
                    if (!tex_coords.empty()) {
                        ss >> msg >> p1 >> t1 >> n1 >> p2 >> t2 >> n2 >> p3 >> t3 >> n3;
                    }
                    else {
                        ss >> msg >> p1 >> n1 >> p2 >> n2 >> p3 >> n3;
                    }

                    indices_positions.push_back(p1 - 1);
                    indices_positions.push_back(p2 - 1);
                    indices_positions.push_back(p3 - 1);

                    if (!tex_coords.empty()) {
                        indices_tex_coords.push_back(t1 - 1);
                        indices_tex_coords.push_back(t2 - 1);
                        indices_tex_coords.push_back(t3 - 1);
                    }

                    indices_normals.push_back(n1 - 1);
                    indices_normals.push_back(n2 - 1);
                    indices_normals.push_back(n3 - 1);

                    indices_materials.push_back(current_material_index);
                    indices_materials.push_back(current_material_index);
                    indices_materials.push_back(current_material_index);
                }
            }
            Logger::log(LogLevel::DBG, "Finished scanning file %s, now creating vertex data", obj_filepath.c_str());

            auto res_vertices = std::vector<VertexData>(indices_positions.size());
            auto res_indices = std::vector<uint16_t>(indices_positions.size());
            for (uint32_t i = 0; i < indices_positions.size(); ++i) {
                VertexData next;
                next.position = positions[indices_positions[i]];
                if (!tex_coords.empty()) {
                    next.tex_coord = tex_coords[indices_tex_coords[i]];
                }
                next.normal = normals[indices_normals[i]];
                next.tex_slot = -1.0f;
                next.material_slot = has_materials ? indices_materials[i] : -1.0f;
                res_vertices[i] = next;
                res_indices[i] = i;
            }
            Logger::log(LogLevel::DBG, "Success");
            Model res = Model(&res_vertices[0], indices_positions.size(), &res_indices[0], indices_positions.size());
            res.set_materials(materials);
            return res;
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
            Logger::log(LogLevel::DBG, "Scanning file %s for materials...", filepath.c_str());
            while (std::getline(fin, line)) {
                std::istringstream ss(line);
                std::string msg;

                ss >> msg;
                if (msg == "newmtl") {
                    result.push_back(material());
                    ss >> result.back().name;
                    Logger::log(LogLevel::DBG, "Found new material %s", result.back().name.c_str());
                }
                else if (msg == "Ns") {
                    ss >> result.back().specular_e;
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
                    ss >> result.back().dissolve;
                }
            }
            Logger::log(LogLevel::DBG, "Finished scanning %s", filepath.c_str());
            return result;
        }
    }
}
